#pragma once

#include "Object.h"

#if LV_USE_SPINBOX && LV_USE_TEXTAREA

namespace lvglcpp {

    enum class SpinboxPart : lv_spinbox_part_t {
        BG = LV_SPINBOX_PART_BG,
        CURSOR = LV_SPINBOX_PART_CURSOR,
    };

    class Spinbox : public Object<Spinbox> {
    public:
        static constexpr uint8_t MAX_DIGIT_COUNT = LV_SPINBOX_MAX_DIGIT_COUNT;

    protected:
        explicit Spinbox(lv_obj_t *other) noexcept: Object(other) {};

    public:

        Spinbox() noexcept: Object(lv_spinbox_create(lv_scr_act(), nullptr)) {};

        template<typename T>
        explicit Spinbox(const Object <T> &parent) noexcept
                : Object(lv_spinbox_create(parent.raw(), nullptr)) {}

        template<typename T>
        explicit Spinbox(const Object <T> &parent, const Spinbox &copy) noexcept
                : Object(lv_spinbox_create(parent.raw(), copy.raw())) {}

        /*
         * SETTERS
         */

        Spinbox &rollover(bool b) {
            lv_spinbox_set_rollover(raw(), b);
            return this->underlying();
        }

        Spinbox &value(int32_t i) {
            lv_spinbox_set_value(raw(), i);
            return this->underlying();
        }

        Spinbox &digit_format(uint8_t digit_count, uint8_t separator_position) {
            lv_spinbox_set_digit_format(raw(), digit_count, separator_position);
            return this->underlying();
        }

        Spinbox &step(uint32_t step) {
            lv_spinbox_set_step(raw(), step);
            return this->underlying();
        }

        Spinbox &range(int32_t range_min, int32_t range_max) {
            lv_spinbox_set_range(raw(), range_min, range_max);
            return this->underlying();
        }

        Spinbox &padding_left(uint8_t padding) {
            lv_spinbox_set_padding_left(raw(), padding);
            return this->underlying();
        }

        /*
         * GETTERS
         */

        [[nodiscard]] bool rollover() const {
            return lv_spinbox_get_rollover(raw());
        }

        [[nodiscard]] int32_t value() const {
            return lv_spinbox_get_value(raw());
        }

        /*
         * OTHER
         */
        void step_next() {
            return lv_spinbox_step_next(raw());
        }

        void step_prev() {
            return lv_spinbox_step_prev(raw());
        }

        void increment() {
            return lv_spinbox_increment(raw());
        }

        void decrement() {
            return lv_spinbox_decrement(raw());
        }
    };
}

#endif // LV_USE_SPINBOX