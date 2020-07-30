#pragma once

#include "Object.h"

#if LV_USE_SLIDER && LV_USE_BAR

namespace lvglcpp {

    enum class SliderType : lv_slider_type_t {
        NORMAL = LV_SLIDER_TYPE_NORMAL,
        SYMMETRICAL = LV_SLIDER_TYPE_SYMMETRICAL,
        RANGE = LV_SLIDER_TYPE_RANGE
    };
    
    enum class SliderPart : uint8_t {
        BG = LV_SLIDER_PART_BG, /** Slider background style. */
        INDIC = LV_SLIDER_PART_INDIC, /** Slider indicator (filled area) style. */
        KNOB = LV_SLIDER_PART_KNOB, /** Slider knob style. */
    };
    
    class Slider final : public Object<Slider> {
    public:

        Slider() : Object(lv_slider_create(lv_scr_act(), nullptr)) {}

        /*
         * SETTERS
         */

        Slider &value(int16_t value, lv_anim_enable_t anim) {
            lv_slider_set_value(get(), value, anim);
            return this->underlying();
        }

        Slider &left_value(int16_t left_value, lv_anim_enable_t anim) {
            lv_slider_set_left_value(get(), left_value, anim);
            return this->underlying();
        }

        Slider &range(int16_t min, int16_t max) {
            lv_slider_set_range(get(), min, max);
            return this->underlying();
        }

        Slider &type(SliderType type) {
            lv_slider_set_type(get(), static_cast<lv_slider_type_t>(type));
            return this->underlying();
        }

        Slider &anim_time(uint16_t anim_time) {
            lv_slider_set_anim_time(get(), anim_time);
            return this->underlying();
        }

        /*
         * GETTERS
         */

        [[nodiscard]] int16_t value() const {
            return lv_slider_get_value(get());
        }

        [[nodiscard]] int16_t left_value() const {
            return lv_slider_get_left_value(get());
        }

        [[nodiscard]] int16_t min_value() const {
            return lv_slider_get_min_value(get());
        }

        [[nodiscard]] int16_t max_value() const {
            return lv_slider_get_max_value(get());
        }

        [[nodiscard]] SliderType slider_type() const {
            return static_cast<SliderType>(lv_slider_get_type(get()));
        }

        [[nodiscard]] uint16_t anim_time() const {
            return lv_slider_get_anim_time(get());
        }

        [[nodiscard]] bool is_dragged() const {
            return lv_slider_is_dragged(get());
        }
        
    };
}

#endif // LV_USE_SLIDER
