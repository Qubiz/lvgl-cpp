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

    class Gauge : public Object<Gauge> {
    protected:
        explicit Gauge(lv_obj_t *other) noexcept: Object(other) {};

    public:

        Gauge() noexcept: Object(lv_gauge_create(lv_scr_act(), nullptr)) {};

        template<typename T>
        explicit Gauge(const Object <T> &parent) noexcept
                : Object(lv_gauge_create(parent.raw(), nullptr)) {}

        template<typename T>
        explicit Gauge(const Object <T> &parent, const Gauge &copy) noexcept
                : Object(lv_gauge_create(parent.raw(), copy.raw())) {}

        /*
         * SETTERS
         */

        Gauge &needle_count(uint8_t needle_cnt, const lv_color_t colors[]) {
            lv_gauge_set_needle_count(raw(), needle_cnt, colors);
            return this->underlying();
        }

        Gauge &value(uint8_t needle_id, int32_t value) {
            lv_gauge_set_value(raw(), needle_id, value);
            return this->underlying();
        }

        Gauge &range(int32_t min, int32_t max) {
            lv_gauge_set_range(raw(), min, max);
            return this->underlying();
        }

        Gauge &critical_value(int32_t value) {
            lv_gauge_set_critical_value(raw(), value);
            return this->underlying();
        }

        Gauge &scale(uint16_t angle, uint8_t line_cnt, uint8_t label_cnt) {
            lv_gauge_set_scale(raw(), angle, line_cnt, label_cnt);
            return this->underlying();
        }

        Gauge &angle_offset(uint16_t angle) {
            lv_gauge_set_angle_offset(raw(), angle);
            return this->underlying();
        }

        Gauge &needle_img(const void *img, lv_coord_t pivot_x, lv_coord_t pivot_y) {
            lv_gauge_set_needle_img(raw(), img, pivot_x, pivot_y);
            return this->underlying();
        }

        Gauge &formatter_cb(lv_gauge_format_cb_t format_cb) {
            lv_gauge_set_formatter_cb(raw(), format_cb);
            return this->underlying();
        }

        /*
         * GETTERS
         */

        [[nodiscard]] int32_t value(uint8_t needle_id) const {
            return lv_gauge_get_value(raw(), needle_id);
        }

        [[nodiscard]] uint8_t needle_count() const {
            return lv_gauge_get_needle_count(raw());
        }

        [[nodiscard]]int32_t min_value() const {
            return lv_gauge_get_min_value(raw());
        }

        [[nodiscard]]int32_t max_value() const {
            return lv_gauge_get_max_value(raw());
        }

        [[nodiscard]]int32_t critical_value() const {
            return lv_gauge_get_critical_value(raw());
        }

        [[nodiscard]] uint8_t label_count() const {
            return lv_gauge_get_label_count(raw());
        }

        [[nodiscard]] uint16_t line_count() const {
            return lv_gauge_get_line_count(raw());
        }

        [[nodiscard]] uint16_t scale_angle() const {
            return lv_gauge_get_scale_angle(raw());
        }

        [[nodiscard]] uint16_t angle_offset() const {
            return lv_gauge_get_angle_offset(raw());
        }

        [[nodiscard]]const void *needle_img() const {
            return lv_gauge_get_needle_img(raw());
        }

        [[nodiscard]]lv_coord_t needle_img_pivot_x() const {
            return lv_gauge_get_needle_img_pivot_x(raw());
        }

        [[nodiscard]]lv_coord_t needle_img_pivot_y() const {
            return lv_gauge_get_needle_img_pivot_y(raw());
        }

    };
}

#endif // LV_USE_GAUGE