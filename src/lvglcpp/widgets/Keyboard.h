#pragma once

#include "Object.h"

#if LV_USE_KEYBOARD && LV_USE_BTNMATRIX && LV_USE_TEXTAREA

namespace lvglcpp {

    enum class KeyboardMode : lv_keyboard_mode_t {
        TEXT_LOWER = LV_KEYBOARD_MODE_TEXT_LOWER,
        TEXT_UPPER = LV_KEYBOARD_MODE_TEXT_UPPER,
        SPECIAL = LV_KEYBOARD_MODE_SPECIAL,
        NUM = LV_KEYBOARD_MODE_NUM,
    };

    enum class KeyboardPart : lv_keyboard_style_t {
        BG = LV_KEYBOARD_PART_BG,
        BTN = LV_KEYBOARD_PART_BTN,
    };

    class Keyboard final : public Object<Keyboard> {
    protected:
        explicit Keyboard(lv_obj_t *other) noexcept: Object(other) {};

    public:

        Keyboard() noexcept: Object(lv_keyboard_create(lv_scr_act(), nullptr)) {};

        explicit Keyboard(const Object<> &parent) noexcept
                : Object(lv_keyboard_create(parent.get(), nullptr)) {}

        explicit Keyboard(const Object<> &parent, const Keyboard &copy) noexcept
                : Object(lv_keyboard_create(parent.get(), copy.get())) {}

        /*
         * SETTERS
         */

        Keyboard &textarea(lv_obj_t *ta) {
            lv_keyboard_set_textarea(get(), ta);
            return this->underlying();
        }

        Keyboard &mode(KeyboardMode mode) {
            lv_keyboard_set_mode(get(), static_cast<lv_keyboard_mode_t>(mode));
            return this->underlying();
        }

        Keyboard &cursor_manage(bool en) {
            lv_keyboard_set_cursor_manage(get(), en);
            return this->underlying();
        }

        Keyboard &map(KeyboardMode mode, std::span<const char *> map) {
            lv_keyboard_set_map(get(), static_cast<lv_keyboard_mode_t>(mode), map.data());
            return this->underlying();
        }

        Keyboard &ctrl_map(KeyboardMode mode, const std::span<lv_btnmatrix_ctrl_t> ctrl_map) {
            lv_keyboard_set_ctrl_map(get(), static_cast<lv_keyboard_mode_t>(mode), ctrl_map.data());
            return this->underlying();
        }

        /*
         * GETTERS
         */

        [[nodiscard]] lv_obj_t *textarea() const {
            return lv_keyboard_get_textarea(get());
        }

        [[nodiscard]] lv_keyboard_mode_t mode() const {
            return lv_keyboard_get_mode(get());
        }

        [[nodiscard]] bool cursor_manage() const {
            return lv_keyboard_get_cursor_manage(get());
        }

        [[nodiscard]] const char **map_array() const {
            return lv_keyboard_get_map_array(get());
        }

        /*
         * OTHER
         */

        void def_event_cb(lv_event_t event) {
            lv_keyboard_def_event_cb(get(), event);
        }

    };
}

#endif // LV_USE_KEYBOARD