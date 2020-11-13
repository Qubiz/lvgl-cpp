#pragma once

#include "Object.h"

#if LV_USE_CHECKBOX

#include "Button.h"

namespace lvglcpp {

    enum class CheckboxPart : lv_checkbox_style_t {
        BG = LV_CHECKBOX_PART_BG,  /**< Style of object background. */
        BULLET = LV_CHECKBOX_PART_BULLET, /**< Style of box (released). */
    };

    class Checkbox : public Object<Checkbox> {
    protected:
        explicit Checkbox(lv_obj_t *other) noexcept: Object(other) {};

    public:

        Checkbox() noexcept: Object(lv_checkbox_create(lv_scr_act(), nullptr)) {};

        template<typename T>
        explicit Checkbox(const Object <T> &parent) noexcept
                : Object(lv_checkbox_create(parent.raw(), nullptr)) {}

        template<typename T>
        explicit Checkbox(const Object <T> &parent, const Checkbox &copy) noexcept
                : Object(lv_checkbox_create(parent.raw(), copy.raw())) {}

        /*
         * SETTERS
         */

        Checkbox &text(const char *text) {
            lv_checkbox_set_text(raw(), text);
            return this->underlying();
        }

        Checkbox &text_static(const char *text) {
            lv_checkbox_set_text_static(raw(), text);
            return this->underlying();
        }

        Checkbox &checked(bool checked) {
            lv_checkbox_set_checked(raw(), checked);
            return this->underlying();
        }

        Checkbox &disabled() {
            lv_checkbox_set_disabled(raw());
            return this->underlying();
        }

        Checkbox &state(ButtonState state) {
            lv_checkbox_set_state(raw(), static_cast<lv_btn_state_t>(state));
            return this->underlying();
        }

        /*
         * GETTERS
         */

        [[nodiscard]] const char *text() const {
            return lv_checkbox_get_text(raw());
        }

        [[nodiscard]] bool checked() const {
            return lv_checkbox_is_checked(raw());
        }

        [[nodiscard]] bool inactive() const {
            return lv_checkbox_is_inactive(raw());
        }

        [[nodiscard]] ButtonState state() const {
            return static_cast<ButtonState>(lv_checkbox_get_state(raw()));
        }

    };
}

#endif // LV_USE_CHECKBOX