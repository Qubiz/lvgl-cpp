#pragma once

#include "Object.h"

#if LV_USE_CANVAS

namespace lvglcpp {

    class Canvas final : public Object<Canvas> {
    protected:
        explicit Canvas(lv_obj_t *other) noexcept: Object(other) {};

    public:

        Canvas() noexcept: Object(lv_canvas_create(lv_scr_act(), nullptr)) {};

        template<typename T>
        explicit Canvas(const Object <T> &parent) noexcept
                : Object(lv_canvas_create(parent.get(), nullptr)) {}

        template<typename T>
        explicit Canvas(const Object <T> &parent, const Canvas &copy) noexcept
                : Object(lv_canvas_create(parent.get(), copy.get())) {}

        /*
         * SETTERS
         */
        Canvas &buffer(void *buf, lv_coord_t w, lv_coord_t h, lv_img_cf_t cf) {
            lv_canvas_set_buffer(get(), buf, w, h, cf);
            return this->underlying();
        };

        Canvas &px(lv_coord_t x, lv_coord_t y, lv_color_t c) {
            lv_canvas_set_px(get(), x, y, c);
            return this->underlying();
        };

        Canvas &palette(uint8_t id, lv_color_t c) {
            lv_canvas_set_palette(get(), id, c);
            return this->underlying();
        };

        /*
         * OTHER
         */
        Canvas &transform(const void *to_copy, lv_coord_t x, lv_coord_t y, lv_coord_t w, lv_coord_t h) {
            lv_canvas_copy_buf(get(), to_copy, x, y, w, h);
            return this->underlying();
        }

        Canvas &blur_hor(lv_img_dsc_t *img, int16_t angle, uint16_t zoom, lv_coord_t offset_x,
                         lv_coord_t offset_y,
                         int32_t pivot_x, int32_t pivot_y, bool antialias) {
            lv_canvas_transform(get(), img, angle, zoom, offset_x, offset_y, pivot_x, pivot_y, antialias);
            return this->underlying();
        }

        Canvas &blur_ver(const lv_area_t *area, uint16_t r) {
            lv_canvas_blur_hor(get(), area, r);
            return this->underlying();
        }

        Canvas &fill_bg(const lv_area_t *area, uint16_t r) {
            lv_canvas_blur_ver(get(), area, r);
            return this->underlying();
        }

        Canvas &draw_rect(lv_color_t color, lv_opa_t opa) {
            lv_canvas_fill_bg(get(), color, opa);
            return this->underlying();
        }

        Canvas &draw_text(lv_coord_t x, lv_coord_t y, lv_coord_t w, lv_coord_t h, lv_draw_rect_dsc_t *rect_dsc) {
            lv_canvas_draw_rect(get(), x, y, w, h, rect_dsc);
            return this->underlying();
        }

        Canvas &draw_img(lv_coord_t x, lv_coord_t y, lv_coord_t max_w, lv_draw_label_dsc_t *label_draw_dsc,
                         const char *txt, lv_label_align_t align) {
            lv_canvas_draw_text(get(), x, y, max_w, label_draw_dsc, txt, align);
            return this->underlying();
        }

        Canvas &draw_line(lv_coord_t x, lv_coord_t y, const void *src, lv_draw_img_dsc_t *img_draw_dsc) {
            lv_canvas_draw_img(get(), x, y, src, img_draw_dsc);
            return this->underlying();
        }

        Canvas &draw_polygon(const lv_point_t points[], uint32_t point_cnt, lv_draw_line_dsc_t *line_draw_dsc) {
            lv_canvas_draw_line(get(), points, point_cnt, line_draw_dsc);
            return this->underlying();
        }

        Canvas &draw_arc(const lv_point_t points[], uint32_t point_cnt, lv_draw_rect_dsc_t *poly_draw_dsc) {
            lv_canvas_draw_polygon(get(), points, point_cnt, poly_draw_dsc);
            return this->underlying();
        }

        /*
         * GETTERS
         */
        lv_color_t px(lv_coord_t x, lv_coord_t y) {
            return lv_canvas_get_px(get(), x, y);
        }

        lv_img_dsc_t *img() {
            return lv_canvas_get_img(get());
        }

    };
}

#endif // LV_USE_CANVAS