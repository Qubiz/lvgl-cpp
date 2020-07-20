#pragma once

#ifndef LVGL_CPP_DISPLAYDRIVER_H
#define LVGL_CPP_DISPLAYDRIVER_H

#include <lvgl.h>
#include <array>

namespace lvglcpp {

    enum class BufferType : uint8_t {
        SINGLE = 1, DOUBLE = 2
    };

    using FlushCallback = void (*)(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p);
    using RounderCallback = void (*)(lv_disp_drv_t *disp_drv, lv_area_t *area);
    using SetPixelCallback = void (*)(lv_disp_drv_t *disp_drv, uint8_t *buf, lv_coord_t buf_w, lv_coord_t x,
                                      lv_coord_t y, lv_color_t color, lv_opa_t opa);

    template<const lv_coord_t HRES, const lv_coord_t VRES, const BufferType BUFFER_TYPE = BufferType::SINGLE, const size_t BUFFER_SIZE_PERCENTAGE = 10>
    class DisplayDriver {
    protected:
        static constexpr auto BUFFER_NUM_PIXELS = (HRES * VRES * BUFFER_SIZE_PERCENTAGE) / 100;
        static constexpr auto BUFFER_SIZE = (LV_COLOR_DEPTH / 8) * BUFFER_NUM_PIXELS;

        using Buffer = std::array<uint8_t, BUFFER_SIZE>;

        DisplayDriver() {
            lv_disp_drv_init(&driver_);

            if constexpr (BUFFER_TYPE == BufferType::SINGLE) {
                lv_disp_buf_init(&disp_buf_, buffers_[0].data(), nullptr, BUFFER_NUM_PIXELS);
            } else {
                lv_disp_buf_init(&disp_buf_, buffers_[0].data(), buffers_[1].data(), BUFFER_NUM_PIXELS);
            }

            driver_.buffer = &disp_buf_;
        }

    public:
        void initialize() {
            driver_.user_data = initUserData();
            driver_.flush_cb = initFlushCallback();
            driver_.rounder_cb = initRounderCallback();
            driver_.set_px_cb = initSetPixelCallback();
            lv_disp_drv_register(&driver_);
        }

    protected:
        virtual lv_disp_drv_user_data_t initUserData() = 0;

        virtual FlushCallback initFlushCallback() = 0;

        virtual RounderCallback initRounderCallback() = 0;

        virtual SetPixelCallback initSetPixelCallback() = 0;

    private:
        std::array<Buffer, static_cast<size_t>(BUFFER_TYPE)> buffers_{};
        lv_disp_drv_t driver_{};
        lv_disp_buf_t disp_buf_{};
    };

}

#endif //LVGL_CPP_DISPLAYDRIVER_H
