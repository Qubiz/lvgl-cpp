#pragma once

#include "Container.h"

#if LV_USE_BTN

namespace lvglcpp {

    enum class ButtonPart : lv_btn_part_t {
        MAIN = LV_BTN_PART_MAIN,
    };

    enum class ButtonState : lv_btn_state_t {
        RELEASED = LV_BTN_STATE_RELEASED,
        PRESSED = LV_BTN_STATE_PRESSED,
        DISABLED = LV_BTN_STATE_DISABLED,
        CHECKED_RELEASED = LV_BTN_STATE_CHECKED_RELEASED,
        CHECKED_PRESSED = LV_BTN_STATE_CHECKED_PRESSED,
        CHECKED_DISABLED = LV_BTN_STATE_CHECKED_DISABLED,
    };

    class Button final : public Object<Button> {
    public:

        Button() : Object(lv_btn_create(lv_scr_act(), nullptr)) {}

        explicit Button(lv_obj_t * other) : Object(other) {}

        /*
         * SETTERS
         */

        Button &checkable(bool toggle) {
            lv_btn_set_checkable(get(), toggle);
            return this->underlying();
        }

        Button &state(ButtonState state) {
            lv_btn_set_state(get(), static_cast<lv_btn_state_t>(state));
            return this->underlying();
        }

        Button &toggle() {
            lv_btn_toggle(get());
            return this->underlying();
        }

        Button &layout(Layout layout) {
            lv_btn_set_layout(get(), static_cast<lv_layout_t>(layout));
            return this->underlying();
        }

        Button &fit4(Fit left, Fit right, Fit top, Fit bottom) {
            lv_btn_set_fit4(get(), static_cast<lv_fit_t>(left), static_cast<lv_fit_t>(right),
                            static_cast<lv_fit_t>(top), static_cast<lv_fit_t>(bottom));
            return this->underlying();
        }

        Button &fit2(Fit hor, Fit ver) {
            lv_btn_set_fit2(get(), static_cast<lv_fit_t>(hor), static_cast<lv_fit_t>(ver));
            return this->underlying();
        }

        Button &fit(Fit fit) {
            lv_btn_set_fit(get(), static_cast<lv_fit_t>(fit));
            return this->underlying();
        }

        /*
         * GETTERS
         */

        [[nodiscard]] ButtonState state() const {
            return static_cast<ButtonState>(lv_btn_get_state(get()));
        }

        [[nodiscard]] bool checkable() const {
            return lv_btn_get_checkable(get());
        }

        [[nodiscard]] lv_layout_t layout() const {
            return lv_btn_get_layout(get());
        }

        [[nodiscard]] Fit fit_left() const {
            return static_cast<Fit>(lv_btn_get_fit_left(get()));
        }

        [[nodiscard]] Fit fit_right() const {
            return static_cast<Fit>(lv_btn_get_fit_right(get()));
        }

        [[nodiscard]] Fit fit_top() const {
            return static_cast<Fit>(lv_btn_get_fit_top(get()));
        }

        [[nodiscard]] Fit fit_bottom() const {
            return static_cast<Fit>(lv_btn_get_fit_bottom(get()));
        }
    };
}

#endif
