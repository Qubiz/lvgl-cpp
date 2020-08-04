#pragma once

#include "Object.h"

#if LV_USE_LINEMETER

namespace lvglcpp {

    enum class LinemeterPart : lv_linemeter_part_t {
        MAIN = LV_LINEMETER_PART_MAIN,
    };

    class Linemeter final : public Object<Linemeter> {
    protected:
        explicit Linemeter(lv_obj_t *other) noexcept: Object(other) {};

    public:

        Linemeter() noexcept: Object(lv_linemeter_create(lv_scr_act(), nullptr)) {};

        template<typename T>
        explicit Linemeter(const Object <T> &parent) noexcept
                : Object(lv_linemeter_create(parent.get(), nullptr)) {}

        template<typename T>
        explicit Linemeter(const Object <T> &parent, const Linemeter &copy) noexcept
                : Object(lv_linemeter_create(parent.get(), copy.get())) {}

        /*
         * SETTERS
         */

        Linemeter &value(int32_t value) {
            lv_linemeter_set_value(get(), value);
            return this->underlying();
        }

        Linemeter &range(int32_t min, int32_t max) {
            lv_linemeter_set_range(get(), min, max);
            return this->underlying();
        }

        Linemeter &scale(uint16_t angle, uint16_t line_cnt) {
            lv_linemeter_set_scale(get(), angle, line_cnt);
            return this->underlying();
        }

        Linemeter &angle_offset(uint16_t angle) {
            lv_linemeter_set_angle_offset(get(), angle);
            return this->underlying();
        }

        Linemeter &mirror(bool mirror) {
            lv_linemeter_set_mirror(get(), mirror);
            return this->underlying();
        }

        /*
         * GETTERS
         */

        [[nodiscard]]int32_t value() const {
            return lv_linemeter_get_value(get());
        }

        [[nodiscard]]int32_t min_value() const {
            return lv_linemeter_get_min_value(get());
        }

        [[nodiscard]]int32_t max_value() const {
            return lv_linemeter_get_max_value(get());
        }

        [[nodiscard]]uint16_t line_count() const {
            return lv_linemeter_get_line_count(get());
        }

        [[nodiscard]]uint16_t scale_angle() const {
            return lv_linemeter_get_scale_angle(get());
        }

        [[nodiscard]]uint16_t angle_offset() const {
            return lv_linemeter_get_angle_offset(get());
        }

        /*
         * OTHER
         */

        void draw_scale(const lv_area_t *clip_area, LinemeterPart part) {
            lv_linemeter_draw_scale(get(), clip_area, static_cast<uint8_t>(part));
        }

        void mirror() {
            lv_linemeter_get_mirror(get());
        }

    };
}

#endif // LV_USE_LINEMETER