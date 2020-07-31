
#include <lvglcpp/LVGLCPP.h>

#include <lvglcpp/sdl/DisplayDriver.h>
#include <iostream>

using namespace lvglcpp;

int main() {

    lv_init();

    static SDLDisplayDriver<LV_HOR_RES_MAX, LV_VER_RES_MAX> display("Test display");
    display.initialize();

    constexpr auto COLOR_MAIN = LV_COLOR_MAKE(0x47, 0x25, 0x6f);

    Style style{};
    style
            .style<prop::RADIUS>(0)
            .style<prop::BORDER_WIDTH>(0)
            .style<prop::PAD_ALL>(0)
            .style<prop::BG_OPA>(LV_OPA_COVER)
            .style<prop::BG_COLOR, ObjectState::FOCUSED>(COLOR_MAIN);

    Object<> background{};
    background
            .add_style(style)
            .size(LV_HOR_RES_MAX, LV_VER_RES_MAX)
            .pos(0, 0)
            .state(ObjectState::FOCUSED);

    display.start(); // Blocking call

    return 0;
}