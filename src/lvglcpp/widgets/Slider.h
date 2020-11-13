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

    class Slider : public Object<Slider> {
    protected:
        explicit Slider(lv_obj_t *other) noexcept: Object(other) {};

    public:

        Slider() noexcept: Object(lv_slider_create(lv_scr_act(), nullptr)) {};

        template<typename T>
        explicit Slider(const Object<T> &parent) noexcept
                : Object(lv_slider_create(parent.raw(), nullptr)) {}

        template<typename T>
        explicit Slider(const Object<T> &parent, const Slider &copy) noexcept
                : Object(lv_slider_create(parent.raw(), copy.raw())) {}

        /*
         * SETTERS
         */

        Slider &value(int16_t value, lv_anim_enable_t anim) {
            lv_slider_set_value(raw(), value, anim);
            return this->underlying();
        }

        Slider &left_value(int16_t left_value, lv_anim_enable_t anim) {
            lv_slider_set_left_value(raw(), left_value, anim);
            return this->underlying();
        }

        Slider &range(int16_t min, int16_t max) {
            lv_slider_set_range(raw(), min, max);
            return this->underlying();
        }

        Slider &type(SliderType type) {
            lv_slider_set_type(raw(), static_cast<lv_slider_type_t>(type));
            return this->underlying();
        }

        Slider &anim_time(uint16_t anim_time) {
            lv_slider_set_anim_time(raw(), anim_time);
            return this->underlying();
        }

        /*
         * GETTERS
         */

        [[nodiscard]] int16_t value() const {
            return lv_slider_get_value(raw());
        }

        [[nodiscard]] int16_t left_value() const {
            return lv_slider_get_left_value(raw());
        }

        [[nodiscard]] int16_t min_value() const {
            return lv_slider_get_min_value(raw());
        }

        [[nodiscard]] int16_t max_value() const {
            return lv_slider_get_max_value(raw());
        }

        [[nodiscard]] SliderType slider_type() const {
            return static_cast<SliderType>(lv_slider_get_type(raw()));
        }

        [[nodiscard]] uint16_t anim_time() const {
            return lv_slider_get_anim_time(raw());
        }

        [[nodiscard]] bool is_dragged() const {
            return lv_slider_is_dragged(raw());
        }

    };
}

#endif // LV_USE_SLIDER
