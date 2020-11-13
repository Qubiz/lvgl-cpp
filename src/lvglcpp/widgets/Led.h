#pragma once

#include "Object.h"

#if LV_USE_LED

namespace lvglcpp {

    enum class LedPart : lv_led_part_t {
        MAIN = LV_LED_PART_MAIN,
    };

    class Led : public Object<Led> {
    protected:
        explicit Led(lv_obj_t *other) noexcept: Object(other) {};

    public:

        Led() noexcept: Object(lv_led_create(lv_scr_act(), nullptr)) {};

        template<typename T>
        explicit Led(const Object <T> &parent) noexcept
                : Object(lv_led_create(parent.raw(), nullptr)) {}

        template<typename T>
        explicit Led(const Object <T> &parent, const Led &copy) noexcept
                : Object(lv_led_create(parent.raw(), copy.raw())) {}

        /*
         * SETTERS
         */

        Led &bright(uint8_t brightness) {
            lv_led_set_bright(raw(), brightness);
            return this->underlying();
        }

        Led &on() {
            lv_led_on(raw());
            return this->underlying();
        }

        Led &off() {
            lv_led_off(raw());
            return this->underlying();
        }

        Led &toggle() {
            lv_led_toggle(raw());
            return this->underlying();
        }

        /*
         * GETTERS
         */

        [[nodiscard]] uint8_t bright() const {
            return lv_led_get_bright(raw());
        }

    };
}

#endif // LV_USE_LED