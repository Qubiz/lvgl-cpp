#pragma once

#include "Object.h"

#if LV_USE_IMG

namespace lvglcpp {

    class Image final : public Object<Image> {
    protected:
        explicit Image(lv_obj_t *other) noexcept: Object(other) {};

        friend class List;

    public:

        Image() noexcept: Object(lv_img_create(lv_scr_act(), nullptr)) {};

        explicit Image(const Object<> &parent) noexcept
                : Object(lv_img_create(parent.get(), nullptr)) {}

        explicit Image(const Object<> &parent, const Image &copy) noexcept
                : Object(lv_img_create(parent.get(), copy.get())) {}

        // Image specific constructors
        explicit Image(const lv_img_dsc_t &source) noexcept {
            set_src(source);
        }

        explicit Image(const lv_img_dsc_t &source, const Object<> &parent) noexcept
                : Image(parent) {
            set_src(source);
        }

        explicit Image(const lv_img_dsc_t &source, const Object<> &parent, const Image &copy) noexcept
                : Image(parent, copy) {
            set_src(source);
        }

        /*
         * SETTERS
         */
        template<typename SourceType>
        Image &set_src(const SourceType &image) {
            lv_img_set_src(get(), &image);
            return this->underlying();
        }

        Image &set_auto_size(bool autosize) {
            lv_img_set_auto_size(get(), autosize);
            return this->underlying();
        }

        Image &set_offset_x(lv_coord_t x) {
            lv_img_set_offset_x(get(), x);
            return this->underlying();
        }

        Image &set_offset_y(lv_coord_t y) {
            lv_img_set_offset_y(get(), y);
            return this->underlying();
        }

        Image &set_pivot(lv_coord_t pivot_x, lv_coord_t pivot_y) {
            lv_img_set_pivot(get(), pivot_x, pivot_y);
            return this->underlying();
        }

        Image &set_angle(int16_t angle) {
            lv_img_set_angle(get(), angle);
            return this->underlying();
        }

        Image &set_zoom(uint16_t zoom) {
            lv_img_set_zoom(get(), zoom);
            return this->underlying();
        }

        Image &set_antialias(bool antialias) {
            lv_img_set_antialias(get(), antialias);
            return this->underlying();
        }

        /*
         * GETTERS
         */

        template<typename SourceType>
        [[nodiscard]] const SourceType *src() const {
            return reinterpret_cast<SourceType *>(lv_img_get_src(get()));
        }

        [[nodiscard]] const char *file_name() const {
            return lv_img_get_file_name(get());
        }

        [[nodiscard]] bool auto_size() const {
            return lv_img_get_auto_size(get());
        }

        [[nodiscard]] lv_coord_t offset_x() const {
            return lv_img_get_offset_x(get());
        }

        [[nodiscard]] lv_coord_t offset_y() const {
            return lv_img_get_offset_y(get());
        }

        [[nodiscard]] std::pair<lv_coord_t, lv_coord_t> offset() const {
            return std::make_pair(offset_x(), offset_y());
        }

        [[nodiscard]] uint16_t angle() const {
            return lv_img_get_angle(get());
        }

        [[nodiscard]] lv_point_t pivot() const {
            lv_point_t point;
            lv_img_get_pivot(get(), &point);
            return point;
        }

        void pivot(lv_point_t &point) const {
            return lv_img_get_pivot(get(), &point);
        }

        [[nodiscard]] uint16_t zoom() const {
            return lv_img_get_zoom(get());
        }

        [[nodiscard]] bool antialias() const {
            return lv_img_get_antialias(get());
        }

    };
}

#endif