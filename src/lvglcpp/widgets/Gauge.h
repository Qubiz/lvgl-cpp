#pragma once

#include "Object.h"

#if LV_USE_GAUGE && LV_USE_LINEMETER

namespace lvglcpp {

    class Gauge;

    enum class GaugePart : lv_gauge_style_t {
        MAIN = LV_GAUGE_PART_MAIN,
        MAJOR = LV_GAUGE_PART_MAJOR,
        NEEDLE = LV_GAUGE_PART_NEEDLE,
    };

    class Gauge final : public Object<Gauge> {
    public:

        Gauge() : Object(lv_gauge_create(lv_scr_act(), nullptr)) {}

        explicit Gauge(lv_obj_t *other) : Object(other) {}

        /*
         * SETTERS
         */

        Gauge &needle_count(uint8_t needle_cnt, const lv_color_t colors[]) {
            lv_gauge_set_needle_count(get(), needle_cnt, colors);
            return this->underlying();
        }

        Gauge &value(uint8_t needle_id, int32_t value) {
            lv_gauge_set_value(get(), needle_id, value);
            return this->underlying();
        }

        Gauge &range(int32_t min, int32_t max) {
            lv_gauge_set_range(get(), min, max);
            return this->underlying();
        }

        Gauge &critical_value(int32_t value) {
            lv_gauge_set_critical_value(get(), value);
            return this->underlying();
        }

        Gauge &scale(uint16_t angle, uint8_t line_cnt, uint8_t label_cnt) {
            lv_gauge_set_scale(get(), angle, line_cnt, label_cnt);
            return this->underlying();
        }

        Gauge &angle_offset(uint16_t angle) {
            lv_gauge_set_angle_offset(get(), angle);
            return this->underlying();
        }

        Gauge &needle_img(const void *img, lv_coord_t pivot_x, lv_coord_t pivot_y) {
            lv_gauge_set_needle_img(get(), img, pivot_x, pivot_y);
            return this->underlying();
        }

        Gauge &formatter_cb(lv_gauge_format_cb_t format_cb) {
            lv_gauge_set_formatter_cb(get(), format_cb);
            return this->underlying();
        }

        /*
         * GETTERS
         */

        [[nodiscard]] int32_t value(uint8_t needle_id) const {
            return lv_gauge_get_value(get(), needle_id);
        }

        [[nodiscard]] uint8_t needle_count() const {
            return lv_gauge_get_needle_count(get());
        }

        [[nodiscard]]int32_t min_value() const {
            return lv_gauge_get_min_value(get());
        }

        [[nodiscard]]int32_t max_value() const {
            return lv_gauge_get_max_value(get());
        }

        [[nodiscard]]int32_t critical_value() const {
            return lv_gauge_get_critical_value(get());
        }

        [[nodiscard]] uint8_t label_count() const {
            return lv_gauge_get_label_count(get());
        }

        [[nodiscard]] uint16_t line_count() const {
            return lv_gauge_get_line_count(get());
        }

        [[nodiscard]] uint16_t scale_angle() const {
            return lv_gauge_get_scale_angle(get());
        }

        [[nodiscard]] uint16_t angle_offset() const {
            return lv_gauge_get_angle_offset(get());
        }

        [[nodiscard]]const void *needle_img() const {
            return lv_gauge_get_needle_img(get());
        }

        [[nodiscard]]lv_coord_t needle_img_pivot_x() const {
            return lv_gauge_get_needle_img_pivot_x(get());
        }

        [[nodiscard]]lv_coord_t needle_img_pivot_y() const {
            return lv_gauge_get_needle_img_pivot_y(get());
        }

    };
}

#endif // LV_USE_GAUGE