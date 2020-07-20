#include <zephyr.h>
#include <device.h>

#include <drivers/display.h>

#include <lvglcpp/zephyr/DisplayDriver.hpp>
#include <lvglcpp/LVGLCPP.h>

#include <logging/log.h>

#include <memory>

LOG_MODULE_REGISTER(MAIN, LOG_LEVEL_DBG);

using namespace lvglcpp;

device *display_device = nullptr;

void main() {
    display_blanking_off(display_device);

    LOG_INF("Starting main loop!");

    while (true) {
        lv_task_handler();
        k_msleep(5);
    }
}

std::unique_ptr<ZephyrDisplayDriver<320, 240>> display;

extern "C" inline int lvgl_init(device *);

inline int lvgl_init(device *dev) {

    display_device = device_get_binding("DISPLAY");

    if (display_device == nullptr) {
        LOG_ERR("Unable to find display device...");
        return -ENODEV;
    }

    // Log print function. Receives "Log Level", "File path", "Line number", "Function name" and "Description".
    lv_log_register_print_cb([](lv_log_level_t level, const char *, uint32_t, const char *,
                                const char *description) {
        uint8_t zephyr_level = LOG_LEVEL_DBG - level;
        Z_LOG(zephyr_level, "%s", log_strdup(description));
    });

    lv_init();

    display = std::make_unique<ZephyrDisplayDriver<320, 240>>(display_device);
    display->initialize();

    static lv_style_t style{};
    lv_style_init(&style);

    constexpr auto COLOR_MAIN = LV_COLOR_MAKE(0x0C, 0xD5, 0xEA);
    constexpr auto COLOR_GRAD = LV_COLOR_MAKE(0x47, 0x26, 0x70);

    Object<> background{};
    background
            .add_style(&style)
            .size(LV_HOR_RES_MAX, LV_VER_RES_MAX)
            .pos(0, 0)
            .style<prop::BG_OPA>(LV_OPA_COVER)
            .style<prop::BG_COLOR>(COLOR_MAIN)
            .style<prop::BG_GRAD_COLOR>(COLOR_GRAD)
            .style<prop::BG_GRAD_DIR>(LV_GRAD_DIR_VER)
            .style<prop::RADIUS>(0)
            .style<prop::BORDER_WIDTH>(0);

    return 0;
}

SYS_INIT(lvgl_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);