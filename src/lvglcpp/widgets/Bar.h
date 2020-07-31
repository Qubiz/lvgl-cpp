#pragma once

#include "Object.h"

#if LV_USE_BAR

namespace lvglcpp {

    enum class BarType : lv_bar_type_t {
        NORMAL = LV_BAR_TYPE_NORMAL,
        SYMMETRICAL = LV_BAR_TYPE_SYMMETRICAL,
        CUSTOM = LV_BAR_TYPE_CUSTOM,
    };

    enum class BarPart : lv_bar_part_t {
        BG = LV_BAR_PART_BG,
        INDIC = LV_BAR_PART_INDIC
    };

    class Bar final : public Object<Bar> {
    public:
        static constexpr auto ANIM_STATE_START = LV_BAR_ANIM_STATE_START;
        static constexpr auto ANIM_STATE_END = LV_BAR_ANIM_STATE_END;
        static constexpr auto ANIM_STATE_INV = LV_BAR_ANIM_STATE_INV;
        static constexpr auto ANIM_STATE_NORM = LV_BAR_ANIM_STATE_NORM;

    protected:
        explicit Bar(lv_obj_t *other) noexcept: Object(other) {};

    public:

        Bar() noexcept: Object(lv_bar_create(lv_scr_act(), nullptr)) {};

        explicit Bar(const Object<> &parent) noexcept
                : Object(lv_bar_create(parent.get(), nullptr)) {}

        explicit Bar(const Object<> &parent, const Bar &copy) noexcept
                : Object(lv_bar_create(parent.get(), copy.get())) {}

        /*
         * SETTERS
         */

        Bar &value(int16_t start, lv_anim_enable_t anim) {
            lv_bar_set_value(get(), start, anim);
            return this->underlying();
        }

        Bar &start_value(int16_t start, lv_anim_enable_t anim) {
            lv_bar_set_start_value(get(), start, anim);
            return this->underlying();
        }

        Bar &range(int16_t min, int16_t max) {
            lv_bar_set_range(get(), min, max);
            return this->underlying();
        }

        Bar &type(BarType type) {
            lv_bar_set_type(get(), static_cast<lv_bar_type_t>(type));
            return this->underlying();
        }

        Bar &anim_time(uint16_t anim_time) {
            lv_bar_set_anim_time(get(), anim_time);
            return this->underlying();
        }

        /*
         * GETTERS
         */

        [[nodiscard]] int16_t value() const {
            return lv_bar_get_value(get());
        }

        [[nodiscard]] int16_t start_value() const {
            return lv_bar_get_start_value(get());
        }

        [[nodiscard]] int16_t min_value() const {
            return lv_bar_get_min_value(get());
        }

        [[nodiscard]] int16_t max_value() const {
            return lv_bar_get_max_value(get());
        }

        [[nodiscard]] BarType bar_type() const {
            return static_cast<BarType>(lv_bar_get_type(get()));
        }

        [[nodiscard]] uint16_t anim_time() const {
            return lv_bar_get_anim_time(get());
        }

    };
}

#endif
