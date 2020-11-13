
#include <lvglcpp/LVGLCPP.h>

#include <lvglcpp/sdl/DisplayDriver.h>
#include <iostream>

using namespace lvglcpp;

static void blank(DisplayDriverBase &driver) {
    driver.blanking(true);
}

int main() {

    lv_init();

    static SDLDisplayDriver<LV_HOR_RES_MAX, LV_VER_RES_MAX> display("Test display");
    display.initialize();

    blank(display);

    constexpr auto COLOR_MAIN = LV_COLOR_MAKE(0x47, 0x25, 0x6f);

    Style style{};
    style
            .style<prop::RADIUS>(0)
            .style<prop::BORDER_WIDTH>(0)
            .style<prop::PAD_ALL>(0)
            .style<prop::BG_OPA>(LV_OPA_COVER)
            .style<prop::BG_COLOR, ObjectState::FOCUSED>(COLOR_MAIN);


//    Screen screen;
//    screen
//            .add_style(style)
//            .size(LV_HOR_RES_MAX, LV_VER_RES_MAX)
//            .pos(0, 0)
//            .state(ObjectState::FOCUSED);

    List list;

    std::array<Button, 7> list_buttons{
            Button(list.add_btn(nullptr, "Button 0")),
            Button(list.add_btn(nullptr, "Button 1")),
            Button(list.add_btn(nullptr, "Button 2")),
            Button(list.add_btn(nullptr, "Button 3")),
            Button(list.add_btn(nullptr, "Button 4")),
            Button(list.add_btn(nullptr, "Button 5")),
            Button(list.add_btn(nullptr, "Button 6")),
    };

    lv_task_create([](lv_task_t *task) {
        static bool down = true;
        auto list = reinterpret_cast<List *>(task->user_data);
        Button button(list->btn_selected());
        if (down) {
            if (auto next = list->next_btn(button); next.has_value()) {
                list->focus_btn(next.value());
            } else {
                down = false;
            }
        } else {
            if (auto prev = list->prev_btn(button); prev.has_value()) {
                list->focus_btn(prev.value());
            } else {
                down = true;
            }
        }

    }, 1000, LV_TASK_PRIO_HIGHEST, &list);

    list.focus_btn(list_buttons[0]);

//    screen.load();

//    Screen screen2;
//
//    Object<> background(screen2);
//    background
//            .add_style(style)
//            .size(LV_HOR_RES_MAX, LV_VER_RES_MAX)
//            .pos(0, 0)
//            .state(ObjectState::FOCUSED)
//            .style<prop::BG_COLOR>(COLOR_MAIN);

//    screen2.load();

    display.start(); // Blocking call

    return 0;
}