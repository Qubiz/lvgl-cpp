
#include <lvglcpp/LVGLCPP.h>

#include <lvglcpp/sdl/DisplayDriver.h>
#include <iostream>

using namespace lvglcpp;

int main() {

    lv_init();

    static SDLDisplayDriver<LV_HOR_RES_MAX, LV_VER_RES_MAX> display("Test display");
    display.initialize();

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

    Calendar calendar{};
    std::array<const char *, 7> day_names{
            "Z", "M", "D",
            "W", "D", "V", "Z"
    };
    calendar.size(LV_HOR_RES_MAX, LV_VER_RES_MAX);
    calendar.day_names(day_names);
    calendar.today_date({2020, 7, 29});
    calendar.showed_date({2020, 7, 29});
    display.start(); // Blocking call

    return 0;
}