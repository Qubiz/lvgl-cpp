#include <zephyr.h>
#include <device.h>

#include <drivers/display.h>

#include <lvglcpp/zephyr/DisplayDriver.hpp>
#include <lvglcpp/LVGLCPP.h>

#include <logging/log.h>

#include <memory>

LOG_MODULE_REGISTER(MAIN, LOG_LEVEL_DBG);

using namespace lvglcpp;

std::unique_ptr<ZephyrDisplayDriver<320, 240>> display;

void main() {
    constexpr auto COLOR_MAIN = LV_COLOR_MAKE(0x0C, 0xD5, 0xEA);

    Style style{};
    style
            .style<prop::BG_OPA>(LV_OPA_COVER)
            .style<prop::BG_COLOR>(COLOR_MAIN)
            .style<prop::RADIUS>(0)
            .style<prop::BORDER_WIDTH>(0);


    Object<> background{};
    background
            .add_style(style)
            .size(LV_HOR_RES_MAX, LV_VER_RES_MAX)
            .pos(0, 0);

    Label label(background);
    label.style<prop::TEXT_COLOR>(lv_color_hex(0xf7f7f7))
            .text_fmt("The value is: %d", lv_tick_get())
            .align(ObjectAlign::CENTER);

    lv_task_create([](lv_task_t *task) {
        auto *label = reinterpret_cast<Label*>(task->user_data);
        label->text_fmt("The value is: %d", lv_tick_get() / 1000);
    }, 1000, LV_TASK_PRIO_HIGHEST, &label);

    display->blanking(false);

    while (true) {
        lv_task_handler();
        k_msleep(5);
    }
}

extern "C" inline int lvgl_init(device *);

int lvgl_init(device *dev) {

    LOG_DBG("LVGL Initialization...");

    auto display_device = device_get_binding("DISPLAY");

    if (display_device == nullptr) {
        LOG_ERR("Unable to find display device...");
        return -ENODEV;
    }

    lv_init();

    display = std::make_unique<ZephyrDisplayDriver<320, 240>>(display_device);
    display->initialize();

    return 0;
}

SYS_INIT(lvgl_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);