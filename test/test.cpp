
#include <thread>
#include <chrono>
#include <atomic>

#include <lvgl.h>
#include <SDL2/SDL.h>
#include <display/monitor.h>

using namespace std::chrono_literals;

template<const size_t WIDTH, const size_t HEIGHT>
class Display {
    static constexpr auto BUFFER_SIZE = WIDTH * 120;
    using DisplayType = Display<WIDTH, HEIGHT>;
public:
    Display() {
        lv_disp_buf_init(&disp_buf_, buffer_.data(), nullptr, BUFFER_SIZE);
        lv_disp_drv_init(&disp_drv_);
        disp_drv_.buffer = &disp_buf_;
        disp_drv_.flush_cb = monitor_flush;
        lv_disp_drv_register(&disp_drv_);
    }

private:
    lv_disp_drv_t disp_drv_{};
    lv_disp_buf_t disp_buf_{};
    std::array<lv_color_t, BUFFER_SIZE> buffer_;

};

int main() {
    lv_init();
    monitor_init();
    SDL_CreateThread([](void *data) -> int {
        while (true) {
            SDL_Delay(5);
            lv_tick_inc(5);
        }
        return 0;
    }, "tick", nullptr);

    Display<LV_HOR_RES_MAX, LV_VER_RES_MAX> display;

    while (true) {
        lv_task_handler();
        std::this_thread::sleep_for(5ms);
    }

    return 0;
}