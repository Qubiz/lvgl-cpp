#pragma once

#include "Object.h"

#if LV_USE_LED

namespace lvglcpp {

    enum class LedPart : lv_led_part_t {
        MAIN = LV_LED_PART_MAIN,
    };

    class Led final : public Object<Led> {
    protected:
        explicit Led(lv_obj_t *other) noexcept: Object(other) {};

    public:

        Led() noexcept: Object(lv_led_create(lv_scr_act(), nullptr)) {};

        explicit Led(const Object<> &parent) noexcept
                : Object(lv_led_create(parent.get(), nullptr)) {}

        explicit Led(const Object<> &parent, const Led &copy) noexcept
                : Object(lv_led_create(parent.get(), copy.get())) {}

        /*
         * SETTERS
         */

        Led &bright(uint8_t brightness) {
            lv_led_set_bright(get(),brightness);
            return this->underlying();
        }

        Led &on() {
            lv_led_on(get());
            return this->underlying();
        }

        Led &off() {
            lv_led_off(get());
            return this->underlying();
        }

        Led &toggle() {
            lv_led_toggle(get());
            return this->underlying();
        }

        /*
         * GETTERS
         */

        [[nodiscard]] uint8_t bright() const {
            return lv_led_get_bright(get());
        }

    };
}

#endif // LV_USE_LED