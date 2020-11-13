#pragma once

#include "Object.h"

#if LV_USE_LINE

#include <span>

namespace lvglcpp {

    enum class LinePart : lv_line_style_t {
        MAIN = LV_LINE_PART_MAIN,
    };

    class Line : public Object<Line> {
    protected:
        explicit Line(lv_obj_t *other) noexcept: Object(other) {};

    public:

        Line() noexcept: Object(lv_line_create(lv_scr_act(), nullptr)) {};

        template<typename T>
        explicit Line(const Object <T> &parent) noexcept
                : Object(lv_line_create(parent.raw(), nullptr)) {}

        template<typename T>
        explicit Line(const Object <T> &parent, const Line &copy) noexcept
                : Object(lv_line_create(parent.raw(), copy.raw())) {}

        /*
         * SETTERS
         */

        Line &points(std::span<lv_point_t> points) {
            lv_line_set_points(raw(), points.data(), points.size());
            return this->underlying();
        }

        Line &auto_size(bool enabled) {
            lv_line_set_auto_size(raw(), enabled);
            return this->underlying();
        }

        Line &y_invert(bool enabled) {
            lv_line_set_y_invert(raw(), enabled);
            return this->underlying();
        }

        /*
         * GETTERS
         */

        [[nodiscard]] bool auto_size() const {
            return lv_line_get_auto_size(raw());
        }

        [[nodiscard]] bool y_invert() const {
            return lv_line_get_y_invert(raw());
        }

    };
}

#endif // LV_USE_LINE