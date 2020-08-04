#pragma once

#include "Object.h"

#if LV_USE_SPINNER && LV_USE_ARC && LV_USE_ANIMATION

namespace lvglcpp {

    enum class SpinnerType : lv_spinner_type_t {
        SPINNING_ARC = LV_SPINNER_TYPE_SPINNING_ARC,
        FILLSPIN_ARC = LV_SPINNER_TYPE_FILLSPIN_ARC,
        CONSTANT_ARC = LV_SPINNER_TYPE_CONSTANT_ARC,
    };

    enum class SpinnerDirection : lv_spinner_dir_t {
        FORWARD = LV_SPINNER_DIR_FORWARD,
        BACKWARD = LV_SPINNER_DIR_BACKWARD,
    };

    enum class SpinnerPart : lv_spinner_style_t {
        BG = LV_SPINNER_PART_BG,
        INDIC = LV_SPINNER_PART_INDIC,
    };


    class Spinner final : public Object<Spinner> {
    protected:
        explicit Spinner(lv_obj_t *other) noexcept: Object(other) {};

    public:

        Spinner() noexcept: Object(lv_spinner_create(lv_scr_act(), nullptr)) {};

        template<typename T>
        explicit Spinner(const Object <T> &parent) noexcept
                : Object(lv_spinner_create(parent.get(), nullptr)) {}

        template<typename T>
        explicit Spinner(const Object <T> &parent, const Spinner &copy) noexcept
                : Object(lv_spinner_create(parent.get(), copy.get())) {}

        /*
         * SETTERS
         */

        Spinner &arc_length(lv_anim_value_t deg) {
            lv_spinner_set_arc_length(get(), deg);
            return this->underlying();
        }

        Spinner &spin_time(uint16_t time) {
            lv_spinner_set_spin_time(get(), time);
            return this->underlying();
        }

        Spinner &type(SpinnerType type) {
            lv_spinner_set_type(get(), static_cast<lv_spinner_type_t>(type));
            return this->underlying();
        }

        Spinner &dir(SpinnerDirection dir) {
            lv_spinner_set_dir(get(), static_cast<lv_spinner_dir_t>(dir));
            return this->underlying();
        }

        /*
         * GETTERS
         */

        [[nodiscard]] lv_anim_value_t arc_length() const {
            return lv_spinner_get_arc_length(get());
        }

        [[nodiscard]] uint16_t spin_time() const {
            return lv_spinner_get_spin_time(get());
        }

        [[nodiscard]] SpinnerType spinner_type() const {
            return static_cast<SpinnerType>(lv_spinner_get_type(get()));
        }

        [[nodiscard]] SpinnerDirection dir(lv_obj_t *spinner) const {
            return static_cast<SpinnerDirection>(lv_spinner_get_dir(get()));
        }

    };
}

#endif // LV_USE_SPINNER