#pragma once

#include <lvglcpp/hal/DisplayDriver.h>
#include <device.h>
#include <drivers/display.h>

namespace lvglcpp {

    template<
            const lv_coord_t HRES,
            const lv_coord_t VRES,
            const lvglcpp::BufferType BUFFER_TYPE = lvglcpp::BufferType::SINGLE,
            const size_t BUFFER_SIZE_PERCENTAGE = 10
    >
    class ZephyrDisplayDriver : public lvglcpp::DisplayDriver<HRES, VRES, BUFFER_TYPE, BUFFER_SIZE_PERCENTAGE> {
    public:
        explicit ZephyrDisplayDriver(device *display_device) : display_device_(display_device) {
            display_get_capabilities(display_device_, &capabilities_);
        }

    protected:
        void *initUserData() override {
            return this;
        }

        lvglcpp::FlushCallback initFlushCallback() override {
            switch (capabilities_.current_pixel_format) {
                case PIXEL_FORMAT_ARGB_8888:
                    return flush<4>();
                case PIXEL_FORMAT_RGB_888:
                    return flush<3>();
                case PIXEL_FORMAT_RGB_565:
                case PIXEL_FORMAT_BGR_565:
                    return flush<2>();
                case PIXEL_FORMAT_MONO01:
                case PIXEL_FORMAT_MONO10:
                    return nullptr;
            }

            return nullptr;
        }

        lvglcpp::RounderCallback initRounderCallback() override {
            return nullptr;
        }

        lvglcpp::SetPixelCallback initSetPixelCallback() override {
            switch (capabilities_.current_pixel_format) {
                case PIXEL_FORMAT_ARGB_8888: {
                    if constexpr (LV_COLOR_DEPTH == 32) {
                        return nullptr;
                    } else {
                        return setPixel<4>();
                    }
                }
                case PIXEL_FORMAT_RGB_888:
                    return setPixel<3>();
                case PIXEL_FORMAT_RGB_565:
                case PIXEL_FORMAT_BGR_565:
                    if constexpr (LV_COLOR_DEPTH == 16) {
                        return nullptr;
                    } else {
                        return setPixel<2>();
                    }
                case PIXEL_FORMAT_MONO01:
                case PIXEL_FORMAT_MONO10:
                    return nullptr;
            }

            return nullptr;
        }

    public:

        template<const size_t BUFFER_BYTES_PER_PIXEL>
        lvglcpp::FlushCallback flush() {
            return [](lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) {
                auto ctx = reinterpret_cast<ZephyrDisplayDriver *>(disp_drv->user_data);

                const uint16_t width = area->x2 - area->x1 + 1;
                const uint16_t height = area->y2 - area->y1 + 1;

                display_buffer_descriptor desc{width * height * BUFFER_BYTES_PER_PIXEL, width, height, width};
                desc.buf_size = width * height * BUFFER_BYTES_PER_PIXEL;
                display_write(ctx->display_device_, area->x1, area->y1, &desc, (void *) color_p);
                lv_disp_flush_ready(disp_drv);
            };
        }

        template<const uint8_t BYTES_PER_PIXEL>
        lvglcpp::SetPixelCallback setPixel() {
            if constexpr (BYTES_PER_PIXEL == 1) {
                return nullptr;
            }

            return [](lv_disp_drv_t *disp_drv, uint8_t *buf, lv_coord_t buf_w, lv_coord_t x, lv_coord_t y,
                      lv_color_t color, lv_opa_t opa) {
                if constexpr (BYTES_PER_PIXEL == 4) {
                    auto *buf_xy = reinterpret_cast<uint32_t *>(buf + x * BYTES_PER_PIXEL +
                                                                y * BYTES_PER_PIXEL * buf_w);
                    *buf_xy = lv_color_to32(color);
                    return;
                }

                if constexpr (BYTES_PER_PIXEL == 3) {
                    uint8_t *buf_xy = buf + x * BYTES_PER_PIXEL + y * BYTES_PER_PIXEL * buf_w;
                    lv_color32_t converted;

                    if constexpr (LV_COLOR_DEPTH == 32) {
                        if (opa != LV_OPA_COVER) {
                            lv_color_t mix_color{};
                            mix_color.ch.red = *buf_xy;
                            mix_color.ch.green = *(buf_xy + 1);
                            mix_color.ch.blue = *(buf_xy + 2);
                            color = lv_color_mix(color, mix_color, opa);
                        }
                    }

                    converted.full = lv_color_to32(color);
                    *buf_xy = converted.ch.red;
                    *(buf_xy + 1) = converted.ch.green;
                    *(buf_xy + 2) = converted.ch.blue;
                    return;
                }

                if constexpr (BYTES_PER_PIXEL == 2) {
                    auto *buf_xy = reinterpret_cast<uint16_t *>(buf + x * BYTES_PER_PIXEL +
                                                                y * BYTES_PER_PIXEL * buf_w);
                    *buf_xy = lv_color_to16(color);
                    return;
                }
            };
        }

        void blanking(bool enabled) {
            if (enabled) {
                display_blanking_on(display_device_);
            } else {
                display_blanking_off(display_device_);
            }
        }

    private:
        device *display_device_;
        display_capabilities capabilities_{};
    };

}