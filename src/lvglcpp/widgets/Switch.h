#pragma once

#include "Object.h"

#if LV_USE_SWITCH && LV_USE_SLIDER

namespace lvglcpp {

    enum class SwitchPart : lv_switch_part_t {
        BG = LV_SWITCH_PART_BG, /**< Switch background. */
        INDIC = LV_SWITCH_PART_INDIC, /**< Switch fill area. */
        KNOB = LV_SWITCH_PART_KNOB, /**< Switch knob. */
    };

    class Switch : public Object<Switch> {
    protected:
        explicit Switch(lv_obj_t *other) noexcept: Object(other) {};

    public:

        Switch() noexcept: Object(lv_switch_create(lv_scr_act(), nullptr)) {};

        template<typename T>
        explicit Switch(const Object <T> &parent) noexcept
                : Object(lv_switch_create(parent.raw(), nullptr)) {}

        template<typename T>
        explicit Switch(const Object <T> &parent, const Switch &copy) noexcept
                : Object(lv_switch_create(parent.raw(), copy.raw())) {}

        /*
         * SETTERS
         */

        Switch &on(lv_anim_enable_t anim) {
            lv_switch_on(raw(), anim);
            return this->underlying();
        }

        Switch &off(lv_anim_enable_t anim) {
            lv_switch_off(raw(), anim);
            return this->underlying();
        }

        Switch &toggle(lv_anim_enable_t anim) {
            lv_switch_toggle(raw(), anim);
            return this->underlying();
        }

        Switch &anim_time(uint16_t anim_time) {
            lv_switch_set_anim_time(raw(), anim_time);
            return this->underlying();
        }

        /*
         * GETTERS
         */

        [[nodiscard]] bool state() const {
            return lv_switch_get_state(raw());
        }

        [[nodiscard]] uint16_t anim_time() const {
            return lv_switch_get_anim_time(raw());
        }

    };
}

#endif // LV_USE_SWITCH