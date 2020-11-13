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

    class Keyboard : public Object<Keyboard> {
    protected:
        explicit Keyboard(lv_obj_t *other) noexcept: Object(other) {};

    public:

        Keyboard() noexcept: Object(lv_keyboard_create(lv_scr_act(), nullptr)) {};

        template<typename T>
        explicit Keyboard(const Object <T> &parent) noexcept
                : Object(lv_keyboard_create(parent.raw(), nullptr)) {}

        template<typename T>
        explicit Keyboard(const Object <T> &parent, const Keyboard &copy) noexcept
                : Object(lv_keyboard_create(parent.raw(), copy.raw())) {}

        /*
         * SETTERS
         */

        Keyboard &textarea(lv_obj_t *ta) {
            lv_keyboard_set_textarea(raw(), ta);
            return this->underlying();
        }

        Keyboard &mode(KeyboardMode mode) {
            lv_keyboard_set_mode(raw(), static_cast<lv_keyboard_mode_t>(mode));
            return this->underlying();
        }

        Keyboard &cursor_manage(bool en) {
            lv_keyboard_set_cursor_manage(raw(), en);
            return this->underlying();
        }

        Keyboard &map(KeyboardMode mode, std::span<const char *> map) {
            lv_keyboard_set_map(raw(), static_cast<lv_keyboard_mode_t>(mode), map.data());
            return this->underlying();
        }

        Keyboard &ctrl_map(KeyboardMode mode, const std::span<lv_btnmatrix_ctrl_t> ctrl_map) {
            lv_keyboard_set_ctrl_map(raw(), static_cast<lv_keyboard_mode_t>(mode), ctrl_map.data());
            return this->underlying();
        }

        /*
         * GETTERS
         */

        [[nodiscard]] lv_obj_t *textarea() const {
            return lv_keyboard_get_textarea(raw());
        }

        [[nodiscard]] lv_keyboard_mode_t mode() const {
            return lv_keyboard_get_mode(raw());
        }

        [[nodiscard]] bool cursor_manage() const {
            return lv_keyboard_get_cursor_manage(raw());
        }

        [[nodiscard]] const char **map_array() const {
            return lv_keyboard_get_map_array(raw());
        }

        /*
         * OTHER
         */

        void def_event_cb(lv_event_t event) {
            lv_keyboard_def_event_cb(raw(), event);
        }

    };
}

#endif // LV_USE_KEYBOARD