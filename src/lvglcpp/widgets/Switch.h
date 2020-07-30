#pragma once

#include "Object.h"

#if LV_USE_SWITCH && LV_USE_SLIDER

namespace lvglcpp {

    enum class SwitchPart : lv_switch_part_t {
        BG = LV_SWITCH_PART_BG, /**< Switch background. */
        INDIC = LV_SWITCH_PART_INDIC, /**< Switch fill area. */
        KNOB = LV_SWITCH_PART_KNOB, /**< Switch knob. */
    };

    class Switch final : public Object<Switch> {
    public:

        Switch() : Object(lv_switch_create(lv_scr_act(), nullptr)) {}

        /*
         * SETTERS
         */

        Switch & on(lv_anim_enable_t anim) {
            lv_switch_on(get(), anim);
            return this->underlying();
        }
        Switch &off(lv_anim_enable_t anim) {
            lv_switch_off(get(), anim);
            return this->underlying();
        }
        Switch & toggle(lv_anim_enable_t anim) {
            lv_switch_toggle(get(), anim);
            return this->underlying();
        }
        Switch & anim_time(uint16_t anim_time) {
            lv_switch_set_anim_time(get(), anim_time);
            return this->underlying();
        }

        /*
         * GETTERS
         */

        [[nodiscard]] bool state() const {
            return lv_switch_get_state(get());
        }
        [[nodiscard]] uint16_t anim_time() const {
            return lv_switch_get_anim_time(get());
        }

    };
}

#endif // LV_USE_SWITCH