#pragma once

#include "Object.h"

#if LV_USE_CHART

namespace lvglcpp {

    enum class ChartType : lv_chart_type_t {
        NONE = LV_CHART_TYPE_NONE, /**< Don't draw the series*/
        LINE = LV_CHART_TYPE_LINE, /**< Connect the points with lines*/
        COLUMN = LV_CHART_TYPE_COLUMN, /**< Draw columns*/
        SCATTER = LV_CHART_TYPE_SCATTER, /**< X/Y chart, points and/or lines*/
    };

    enum class ChartUpdateMode : lv_chart_update_mode_t {
        SHIFT = LV_CHART_UPDATE_MODE_SHIFT,     /**< Shift old data to the left and add the new one o the right*/
        CIRCULAR = LV_CHART_UPDATE_MODE_CIRCULAR,  /**< Add the new data in a circular way*/
    };

    enum class ChartAxis : lv_chart_axis_t {
        PRIMARY_Y = LV_CHART_AXIS_PRIMARY_Y,
        SECONDARY_Y = LV_CHART_AXIS_SECONDARY_Y,
    };

    enum class ChartPart : uint8_t {
        BG = LV_CHART_PART_BG,
        SERIES_BG = LV_CHART_PART_SERIES_BG,
        SERIES = LV_CHART_PART_SERIES,
    };

    class Chart final : public Object<Chart> {
    public:

        Chart() : Object(lv_chart_create(lv_scr_act(), nullptr)) {}

        /*
         * ADD/REMOVE
         */

        lv_chart_series_t &add_series(lv_color_t color) {
            return *lv_chart_add_series(get(), color);
        }

        Chart &clear_serie(lv_chart_series_t &serie) {
            lv_chart_clear_serie(get(), &serie);
            return this->underlying();
        }

        /*
         * SETTERS
         */

        Chart &div_line_count(uint8_t hdiv, uint8_t vdiv) {
            lv_chart_set_div_line_count(get(), hdiv, vdiv);
            return this->underlying();
        }

        Chart &y_range(lv_chart_axis_t axis, lv_coord_t ymin, lv_coord_t ymax) {
            lv_chart_set_y_range(get(), axis, ymin, ymax);
            return this->underlying();
        }

        Chart &type(ChartType type) {
            lv_chart_set_type(get(), static_cast<lv_chart_type_t>(type));
            return this->underlying();
        }

        Chart &point_count(uint16_t point_cnt) {
            lv_chart_set_point_count(get(), point_cnt);
            return this->underlying();
        }

        Chart &init_points(lv_chart_series_t &ser, lv_coord_t y) {
            lv_chart_init_points(get(), &ser, y);
            return this->underlying();
        }

        Chart &points(lv_chart_series_t &ser, std::span<lv_coord_t> points) {
            lv_chart_set_point_count(get(), points.size());
            lv_chart_set_points(get(), &ser, points.data());
            return this->underlying();
        }

        Chart &points(lv_chart_series_t &ser, lv_coord_t *y_array) {
            lv_chart_set_points(get(), &ser, y_array);
            return this->underlying();
        }

        Chart &next(lv_chart_series_t &ser, lv_coord_t y) {
            lv_chart_set_next(get(), &ser, y);
            return this->underlying();
        }

        Chart &update_mode(ChartUpdateMode update_mode) {
            lv_chart_set_update_mode(get(), static_cast<lv_chart_update_mode_t>(update_mode));
            return this->underlying();
        }

        Chart &x_tick_length(uint8_t major_tick_len, uint8_t minor_tick_len) {
            lv_chart_set_x_tick_length(get(), major_tick_len, minor_tick_len);
            return this->underlying();
        }

        Chart &y_tick_length(uint8_t major_tick_len, uint8_t minor_tick_len) {
            lv_chart_set_y_tick_length(get(), major_tick_len, minor_tick_len);
            return this->underlying();
        }

        Chart &secondary_y_tick_length(uint8_t major_tick_len, uint8_t minor_tick_len) {
            lv_chart_set_secondary_y_tick_length(get(), major_tick_len, minor_tick_len);
            return this->underlying();
        }

        Chart &x_tick_texts(const char *list_of_values, uint8_t num_tick_marks,
                            lv_chart_axis_options_t options) {
            lv_chart_set_x_tick_texts(get(), list_of_values, num_tick_marks, options);
            return this->underlying();
        }

        Chart &secondary_y_tick_texts(const char *list_of_values, uint8_t num_tick_marks,
                                      lv_chart_axis_options_t options) {
            lv_chart_set_secondary_y_tick_texts(get(), list_of_values, num_tick_marks, options);
            return this->underlying();
        }

        Chart &y_tick_texts(const char *list_of_values, uint8_t num_tick_marks,
                            lv_chart_axis_options_t options) {
            lv_chart_set_y_tick_texts(get(), list_of_values, num_tick_marks, options);
            return this->underlying();
        }

        Chart &x_start_point(lv_chart_series_t &ser, uint16_t index) {
            lv_chart_set_x_start_point(get(), &ser, index);
            return this->underlying();
        }

        Chart &ext_array(lv_chart_series_t &ser, std::span<lv_coord_t> points) {
            lv_chart_set_ext_array(get(), &ser, points.data(), points.size());
            return this->underlying();
        }

        Chart &point_id(lv_chart_series_t &ser, lv_coord_t value, uint16_t index) {
            lv_chart_set_point_id(get(), &ser, value, index);
            return this->underlying();
        }

        Chart &series_axis(lv_chart_series_t &ser, ChartAxis axis) {
            lv_chart_set_series_axis(get(), &ser, static_cast<lv_chart_axis_t>(axis));
            return this->underlying();
        }

        /*
         * GETTERS
         */

        [[nodiscard]] ChartType chart_type() const {
            return static_cast<ChartType>(lv_chart_get_type(get()));
        }

        [[nodiscard]] uint16_t point_count() const {
            return lv_chart_get_point_count(get());
        }

        [[nodiscard]] uint16_t x_start_point(lv_chart_series_t &ser) const {
            return lv_chart_get_x_start_point(&ser);
        }

        [[nodiscard]] lv_coord_t point_id(lv_chart_series_t &ser, uint16_t id) const {
            return lv_chart_get_point_id(get(), &ser, id);
        }

        [[nodiscard]] ChartAxis series_axis(lv_chart_series_t &ser) const {
            return static_cast<ChartAxis>(lv_chart_get_series_axis(get(), &ser));
        }

        /*
         * OTHER
         */

        Chart &refresh() {
            lv_chart_refresh(get());
            return this->underlying();
        }

    };
}

#endif // LV_USE_CHART