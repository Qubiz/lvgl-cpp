#pragma once

#include "Object.h"

#if LV_USE_LINE

namespace lvglcpp {

    enum class LinePart : lv_line_style_t {
        MAIN = LV_LINE_PART_MAIN,
    };

    class Line final : public Object<Line> {
    public:

        Line() : Object(lv_line_create(lv_scr_act(), nullptr)) {}

        /*
         * SETTERS
         */

        Line &points(std::span<lv_point_t> points) {
            lv_line_set_points(get(), points.data(), points.size());
            return this->underlying();
        }

        Line &auto_size(bool enabled) {
            lv_line_set_auto_size(get(), enabled);
            return this->underlying();
        }

        Line &y_invert(bool enabled) {
            lv_line_set_y_invert(get(), enabled);
            return this->underlying();
        }

        /*
         * GETTERS
         */

        [[nodiscard]] bool auto_size() const {
            return lv_line_get_auto_size(get());
        }
        [[nodiscard]] bool y_invert() const {
            return lv_line_get_y_invert(get());
        }

    };
}

#endif // LV_USE_LINE