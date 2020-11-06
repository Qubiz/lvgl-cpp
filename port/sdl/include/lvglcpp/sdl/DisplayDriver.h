#pragma once

#ifndef LVGL_CPP_SDLDISPLAYDRIVER_H
#define LVGL_CPP_SDLDISPLAYDRIVER_H

#include <memory>
#include <thread>

#include <SDL2/SDL.h>

#include <lvglcpp/hal/DisplayDriver.h>

struct SDLWindowDeleter {
    void operator()(SDL_Window *window) { SDL_DestroyWindow(window); }
};

struct SDLRendererDeleter {
    void operator()(SDL_Renderer *renderer) { SDL_DestroyRenderer(renderer); }
};

struct SDLTextureDeleter {
    void operator()(SDL_Texture *texture) { SDL_DestroyTexture(texture); }
};

namespace lvglcpp {

    template<
            const lv_coord_t HRES,
            const lv_coord_t VRES,
            const lvglcpp::BufferType BUFFER_TYPE = lvglcpp::BufferType::SINGLE,
            const size_t BUFFER_SIZE_PERCENTAGE = 10
    >
    class SDLDisplayDriver final : public lvglcpp::DisplayDriver<HRES, VRES, BUFFER_TYPE, BUFFER_SIZE_PERCENTAGE> {
    public:
        explicit SDLDisplayDriver(const char *title) {
            SDL_Init(SDL_INIT_VIDEO);

            SDL_SetEventFilter([](void *user_data, SDL_Event *event) -> int {
                auto ctx = reinterpret_cast<SDLDisplayDriver *>(user_data);

                if (event->type == SDL_QUIT ||
                    event->type == SDL_WINDOWEVENT && event->window.event == SDL_WINDOWEVENT_CLOSE) {
                    ctx->quit_ = true;
                }

                return 1;
            }, this);

            window_ = std::unique_ptr<SDL_Window, SDLWindowDeleter>(
                    SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, HRES, VRES, 0)
            );

            renderer_ = std::unique_ptr<SDL_Renderer, SDLRendererDeleter>(
                    SDL_CreateRenderer(window_.get(), -1, SDL_RENDERER_ACCELERATED)
            );

            texture_ = std::unique_ptr<SDL_Texture, SDLTextureDeleter>(
                    SDL_CreateTexture(renderer_.get(), SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, HRES, VRES)
            );

            SDL_SetTextureBlendMode(texture_.get(), SDL_BLENDMODE_BLEND);
        }

        void start() {
            std::thread tick_handler([](SDLDisplayDriver *disp) {
                while (!disp->quit_) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                    lv_tick_inc(1);
                }

            }, this);

            lv_task_create([](lv_task_t *t) {
                auto disp = reinterpret_cast<SDLDisplayDriver *>(t->user_data);

                disp->refresh();

                if (disp->quit_) {
                    lv_task_del(t);
                }

            }, 10, LV_TASK_PRIO_HIGH, this);

            while (!quit_) {
                lv_task_handler();
                std::this_thread::sleep_for(std::chrono::milliseconds(5));
            }

            if (tick_handler.joinable()) {
                tick_handler.join();
            }
        }

        virtual ~SDLDisplayDriver() {
            SDL_Quit();
        }

    private:
        void refresh() {
            if (refresh_) {
                refresh_ = false;
                update();
            }

            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_WINDOWEVENT
                    && (event.window.event == SDL_WINDOWEVENT_TAKE_FOCUS ||
                        event.window.event == SDL_WINDOWEVENT_EXPOSED)) {

                    update();
                }
            }
        }


        void update() {
            SDL_UpdateTexture(texture_.get(), nullptr, frame_buffer_.data(), HRES * sizeof(uint32_t));
            SDL_RenderClear(renderer_.get());
            SDL_RenderCopy(renderer_.get(), texture_.get(), nullptr, nullptr);
            SDL_RenderPresent(renderer_.get());
        }

        lv_disp_drv_user_data_t initUserData() override {
            return this;
        }

        lvglcpp::FlushCallback initFlushCallback() override {
            return [](lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) {

                auto ctx = reinterpret_cast<SDLDisplayDriver *>(disp_drv->user_data);

                const lv_coord_t hres = disp_drv->rotated == 0 ? disp_drv->hor_res : disp_drv->ver_res;
                const lv_coord_t vres = disp_drv->rotated == 0 ? disp_drv->ver_res : disp_drv->hor_res;

                if (area->x2 < 0 || area->y2 < 0 || area->x1 > hres - 1 || area->y1 > vres - 1) {
                    lv_disp_flush_ready(disp_drv);
                    return;
                }

                if constexpr (LV_COLOR_DEPTH == 32 || LV_COLOR_DEPTH == 24) {
                    int32_t x, y;
                    uint32_t w = lv_area_get_width(area);
                    for (y = area->y1; y <= area->y2 && y < disp_drv->ver_res; y++) {
                        memcpy(&ctx->frame_buffer_[y * HRES + area->x1], color_p, w * sizeof(lv_color_t));
                        color_p += w;
                    }
                } else {
                    int32_t x, y;
                    for (y = area->y1; y <= area->y2 && y < disp_drv->ver_res; y++) {
                        for (x = area->x1; x <= area->x2; x++) {
                            ctx->frame_buffer_[y * disp_drv->hor_res + x] = lv_color_to32(*color_p);
                            color_p++;
                        }
                    }
                }

                ctx->refresh_ = true;
                lv_disp_flush_ready(disp_drv);
            };
        }

        lvglcpp::RounderCallback initRounderCallback() override {
            return nullptr;
        }

        lvglcpp::SetPixelCallback initSetPixelCallback() override {
            return nullptr;
        }

    public:
        void blanking(bool enabled) override {
            // Do nothing
        }

    private:
        std::unique_ptr<SDL_Window, SDLWindowDeleter> window_;
        std::unique_ptr<SDL_Renderer, SDLRendererDeleter> renderer_;
        std::unique_ptr<SDL_Texture, SDLTextureDeleter> texture_;

        std::array<uint32_t, HRES * VRES> frame_buffer_{0x30};

        std::atomic_bool quit_ = false;
        std::atomic_bool refresh_ = false;
    };

}
#endif //LVGL_CPP_SDLDISPLAYDRIVER_H
