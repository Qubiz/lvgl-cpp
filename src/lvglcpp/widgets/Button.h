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

    class Button : public Object<Button> {
    protected:
        explicit Button(lv_obj_t *other) noexcept: Object(other) {};

        friend class List;
        friend class Window;

    public:

        Button(Button &&move) = default;

        Button(const Button &other) = default;

        Button() noexcept: Object(lv_btn_create(lv_scr_act(), nullptr)) {};

        template<typename T>
        explicit Button(const Object<T> &parent) noexcept
                : Object(lv_btn_create(parent.raw(), nullptr)) {}

        template<typename T>
        explicit Button(const Object<T> &parent, const Button &copy) noexcept
                : Object(lv_btn_create(parent.raw(), copy.raw())) {}

        /*
         * SETTERS
         */

        Button &checkable(bool toggle) {
            lv_btn_set_checkable(raw(), toggle);
            return this->underlying();
        }

        Button &state(ButtonState state) {
            lv_btn_set_state(raw(), static_cast<lv_btn_state_t>(state));
            return this->underlying();
        }

        Button &toggle() {
            lv_btn_toggle(raw());
            return this->underlying();
        }

        Button &layout(Layout layout) {
            lv_btn_set_layout(raw(), static_cast<lv_layout_t>(layout));
            return this->underlying();
        }

        Button &fit4(Fit left, Fit right, Fit top, Fit bottom) {
            lv_btn_set_fit4(raw(), static_cast<lv_fit_t>(left), static_cast<lv_fit_t>(right),
                            static_cast<lv_fit_t>(top), static_cast<lv_fit_t>(bottom));
            return this->underlying();
        }

        Button &fit2(Fit hor, Fit ver) {
            lv_btn_set_fit2(raw(), static_cast<lv_fit_t>(hor), static_cast<lv_fit_t>(ver));
            return this->underlying();
        }

        Button &fit(Fit fit) {
            lv_btn_set_fit(raw(), static_cast<lv_fit_t>(fit));
            return this->underlying();
        }

        /*
         * GETTERS
         */

        [[nodiscard]] ButtonState state() const {
            return static_cast<ButtonState>(lv_btn_get_state(raw()));
        }

        [[nodiscard]] bool checkable() const {
            return lv_btn_get_checkable(raw());
        }

        [[nodiscard]] lv_layout_t layout() const {
            return lv_btn_get_layout(raw());
        }

        [[nodiscard]] Fit fit_left() const {
            return static_cast<Fit>(lv_btn_get_fit_left(raw()));
        }

        [[nodiscard]] Fit fit_right() const {
            return static_cast<Fit>(lv_btn_get_fit_right(raw()));
        }

        [[nodiscard]] Fit fit_top() const {
            return static_cast<Fit>(lv_btn_get_fit_top(raw()));
        }

        [[nodiscard]] Fit fit_bottom() const {
            return static_cast<Fit>(lv_btn_get_fit_bottom(raw()));
        }
    };
}

#endif
