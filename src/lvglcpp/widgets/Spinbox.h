#pragma once

#include "Object.h"

#if LV_USE_SPINBOX && LV_USE_TEXTAREA

namespace lvglcpp {

    enum class SpinboxPart : lv_spinbox_part_t {
        BG = LV_SPINBOX_PART_BG,
        CURSOR = LV_SPINBOX_PART_CURSOR,
    };

    class Spinbox final : public Object<Spinbox> {
    public:
        static constexpr uint8_t MAX_DIGIT_COUNT = LV_SPINBOX_MAX_DIGIT_COUNT;

    protected:
        explicit Spinbox(lv_obj_t *other) noexcept: Object(other) {};

    public:

        Spinbox() noexcept: Object(lv_spinbox_create(lv_scr_act(), nullptr)) {};

        template<typename T>
        explicit Spinbox(const Object <T> &parent) noexcept
                : Object(lv_spinbox_create(parent.get(), nullptr)) {}

        template<typename T>
        explicit Spinbox(const Object <T> &parent, const Spinbox &copy) noexcept
                : Object(lv_spinbox_create(parent.get(), copy.get())) {}

        /*
         * SETTERS
         */

        Spinbox &rollover(bool b) {
            lv_spinbox_set_rollover(get(), b);
            return this->underlying();
        }

        Spinbox &value(int32_t i) {
            lv_spinbox_set_value(get(), i);
            return this->underlying();
        }

        Spinbox &digit_format(uint8_t digit_count, uint8_t separator_position) {
            lv_spinbox_set_digit_format(get(), digit_count, separator_position);
            return this->underlying();
        }

        Spinbox &step(uint32_t step) {
            lv_spinbox_set_step(get(), step);
            return this->underlying();
        }

        Spinbox &range(int32_t range_min, int32_t range_max) {
            lv_spinbox_set_range(get(), range_min, range_max);
            return this->underlying();
        }

        Spinbox &padding_left(uint8_t padding) {
            lv_spinbox_set_padding_left(get(), padding);
            return this->underlying();
        }

        /*
         * GETTERS
         */

        [[nodiscard]] bool rollover() const {
            return lv_spinbox_get_rollover(get());
        }

        [[nodiscard]] int32_t value() const {
            return lv_spinbox_get_value(get());
        }

        /*
         * OTHER
         */
        void step_next() {
            return lv_spinbox_step_next(get());
        }

        void step_prev() {
            return lv_spinbox_step_prev(get());
        }

        void increment() {
            return lv_spinbox_increment(get());
        }

        void decrement() {
            return lv_spinbox_decrement(get());
        }
    };
}

#endif // LV_USE_SPINBOX