#pragma once

#include "Object.h"

#if LV_USE_ARC

namespace lvglcpp {

    class Arc : public Object<Arc> {
    protected:
        explicit Arc(lv_obj_t *other) noexcept: Object(other) {};

    public:

        Arc() noexcept: Object(lv_arc_create(lv_scr_act(), nullptr)) {};

        template<typename T>
        explicit Arc(const Object<T> &parent) noexcept
                : Object(lv_arc_create(parent.raw(), nullptr)) {}

        template<typename T>
        explicit Arc(const Object<T> &parent, const Arc &copy) noexcept
                : Object(lv_arc_create(parent.raw(), copy.raw())) {}

        /*
         * SETTERS
         */

        Arc &start_angle(uint16_t start) {
            lv_arc_set_start_angle(raw(), start);
            return this->underlying();
        }

        Arc &end_angle(uint16_t start) {
            lv_arc_set_end_angle(raw(), start);
            return this->underlying();
        }

        Arc &angles(uint16_t start, uint16_t end) {
            lv_arc_set_angles(raw(), start, end);
            return this->underlying();
        }

        Arc &bg_start_angle(uint16_t start) {
            lv_arc_set_bg_start_angle(raw(), start);
            return this->underlying();
        }

        Arc &bg_end_angle(uint16_t start) {
            lv_arc_set_bg_end_angle(raw(), start);
            return this->underlying();
        }

        Arc &bg_angles(uint16_t start, uint16_t end) {
            lv_arc_set_bg_angles(raw(), start, end);
            return this->underlying();
        }

        Arc &rotation(uint16_t rotation) {
            lv_arc_set_rotation(raw(), rotation);
            return this->underlying();
        }

        /*
         * GETTERS
         */

        uint16_t angle_start() {
            return lv_arc_get_angle_start(raw());
        }

        uint16_t angle_end() {
            return lv_arc_get_angle_end(raw());
        }

        uint16_t bg_start_angle() {
            return lv_arc_get_bg_angle_start(raw());
        }

        uint16_t bg_end_angle() {
            return lv_arc_get_bg_angle_end(raw());
        }

    };
}

#endif
