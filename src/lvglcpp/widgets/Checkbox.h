#pragma once

#include "Object.h"

#if LV_USE_CHECKBOX

#include "Button.h"

namespace lvglcpp {

    enum class CheckboxPart : lv_checkbox_style_t {
        BG = LV_CHECKBOX_PART_BG,  /**< Style of object background. */
        BULLET = LV_CHECKBOX_PART_BULLET, /**< Style of box (released). */
    };

    class Checkbox final : public Object<Checkbox> {
    protected:
        explicit Checkbox(lv_obj_t *other) noexcept: Object(other) {};

    public:

        Checkbox() noexcept: Object(lv_checkbox_create(lv_scr_act(), nullptr)) {};

        template<typename T>
        explicit Checkbox(const Object <T> &parent) noexcept
                : Object(lv_checkbox_create(parent.get(), nullptr)) {}

        template<typename T>
        explicit Checkbox(const Object <T> &parent, const Checkbox &copy) noexcept
                : Object(lv_checkbox_create(parent.get(), copy.get())) {}

        /*
         * SETTERS
         */

        Checkbox &text(const char *text) {
            lv_checkbox_set_text(get(), text);
            return this->underlying();
        }

        Checkbox &text_static(const char *text) {
            lv_checkbox_set_text_static(get(), text);
            return this->underlying();
        }

        Checkbox &checked(bool checked) {
            lv_checkbox_set_checked(get(), checked);
            return this->underlying();
        }

        Checkbox &disabled() {
            lv_checkbox_set_disabled(get());
            return this->underlying();
        }

        Checkbox &state(ButtonState state) {
            lv_checkbox_set_state(get(), static_cast<lv_btn_state_t>(state));
            return this->underlying();
        }

        /*
         * GETTERS
         */

        [[nodiscard]] const char *text() const {
            return lv_checkbox_get_text(get());
        }

        [[nodiscard]] bool checked() const {
            return lv_checkbox_is_checked(get());
        }

        [[nodiscard]] bool inactive() const {
            return lv_checkbox_is_inactive(get());
        }

        [[nodiscard]] ButtonState state() const {
            return static_cast<ButtonState>(lv_checkbox_get_state(get()));
        }

    };
}

#endif // LV_USE_CHECKBOX