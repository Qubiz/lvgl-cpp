#pragma once

#include "Object.h"

#include <utility>

#if LV_USE_IMG

namespace lvglcpp {

    class Image : public Object<Image> {
    protected:
        explicit Image(lv_obj_t *other) noexcept: Object(other) {};

        friend class List;

    public:

        Image() noexcept: Object(lv_img_create(lv_scr_act(), nullptr)) {};

        template<typename T>
        explicit Image(const Object <T> &parent) noexcept
                : Object(lv_img_create(parent.raw(), nullptr)) {}

        template<typename T>
        explicit Image(const Object <T> &parent, const Image &copy) noexcept
                : Object(lv_img_create(parent.raw(), copy.raw())) {}

        // Image specific constructors
        explicit Image(const lv_img_dsc_t &source) noexcept
                : Image() {
            set_src(source);
        }

        template<typename T>
        explicit Image(const lv_img_dsc_t &source, const Object <T> &parent) noexcept
                : Image(parent) {
            set_src(source);
        }

        template<typename T>
        explicit Image(const lv_img_dsc_t &source, const Object <T> &parent, const Image &copy) noexcept
                : Image(parent, copy) {
            set_src(source);
        }

        /*
         * SETTERS
         */
        template<typename SourceType>
        Image &set_src(const SourceType &image) {
            lv_img_set_src(raw(), &image);
            return this->underlying();
        }

        Image &set_auto_size(bool autosize) {
            lv_img_set_auto_size(raw(), autosize);
            return this->underlying();
        }

        Image &set_offset_x(lv_coord_t x) {
            lv_img_set_offset_x(raw(), x);
            return this->underlying();
        }

        Image &set_offset_y(lv_coord_t y) {
            lv_img_set_offset_y(raw(), y);
            return this->underlying();
        }

        Image &set_pivot(lv_coord_t pivot_x, lv_coord_t pivot_y) {
            lv_img_set_pivot(raw(), pivot_x, pivot_y);
            return this->underlying();
        }

        Image &set_angle(int16_t angle) {
            lv_img_set_angle(raw(), angle);
            return this->underlying();
        }

        Image &set_zoom(uint16_t zoom) {
            lv_img_set_zoom(raw(), zoom);
            return this->underlying();
        }

        Image &set_antialias(bool antialias) {
            lv_img_set_antialias(raw(), antialias);
            return this->underlying();
        }

        /*
         * GETTERS
         */

        template<typename SourceType>
        [[nodiscard]] const SourceType *src() const {
            return reinterpret_cast<SourceType *>(lv_img_get_src(raw()));
        }

        [[nodiscard]] const char *file_name() const {
            return lv_img_get_file_name(raw());
        }

        [[nodiscard]] bool auto_size() const {
            return lv_img_get_auto_size(raw());
        }

        [[nodiscard]] lv_coord_t offset_x() const {
            return lv_img_get_offset_x(raw());
        }

        [[nodiscard]] lv_coord_t offset_y() const {
            return lv_img_get_offset_y(raw());
        }

        [[nodiscard]] std::pair<lv_coord_t, lv_coord_t> offset() const {
            return std::make_pair(offset_x(), offset_y());
        }

        [[nodiscard]] uint16_t angle() const {
            return lv_img_get_angle(raw());
        }

        [[nodiscard]] lv_point_t pivot() const {
            lv_point_t point;
            lv_img_get_pivot(raw(), &point);
            return point;
        }

        void pivot(lv_point_t &point) const {
            return lv_img_get_pivot(raw(), &point);
        }

        [[nodiscard]] uint16_t zoom() const {
            return lv_img_get_zoom(raw());
        }

        [[nodiscard]] bool antialias() const {
            return lv_img_get_antialias(raw());
        }

    };
}

#endif