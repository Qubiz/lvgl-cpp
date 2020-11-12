#pragma once

#include "Object.h"

#if LV_USE_CONT

namespace lvglcpp {

    enum class Layout : lv_layout_t {
        OFF = LV_LAYOUT_OFF,
        CENTER = LV_LAYOUT_CENTER,
        COLUMN_LEFT = LV_LAYOUT_COLUMN_LEFT,
        COLUMN_MID = LV_LAYOUT_COLUMN_MID,
        COLUMN_RIGHT = LV_LAYOUT_COLUMN_RIGHT,
        ROW_TOP = LV_LAYOUT_ROW_TOP,
        ROW_MID = LV_LAYOUT_ROW_MID,
        ROW_BOTTOM = LV_LAYOUT_ROW_BOTTOM,
        PRETTY_TOP = LV_LAYOUT_PRETTY_TOP,
        PRETTY_MID = LV_LAYOUT_PRETTY_MID,
        PRETTY_BOTTOM = LV_LAYOUT_PRETTY_BOTTOM,
        GRID = LV_LAYOUT_GRID,
    };

    enum class Fit {
        NONE = LV_FIT_NONE,
        TIGHT = LV_FIT_TIGHT,
        PARENT = LV_FIT_PARENT,
        MAX = LV_FIT_MAX,
    };

    enum class ContainerPart {
        MAIN = LV_OBJ_PART_MAIN
    };

    class Container : public Object<Container> {
    protected:
        explicit Container(lv_obj_t *other) noexcept: Object(other) {};

    public:

        Container() noexcept: Object(lv_cont_create(lv_scr_act(), nullptr)) {};

        template<typename T>
        explicit Container(const Object <T> &parent) noexcept
                : Object(lv_cont_create(parent.raw(), nullptr)) {}

        template<typename T>
        explicit Container(const Object <T> &parent, const Container &copy) noexcept
                : Object(lv_cont_create(parent.raw(), copy.raw())) {}

        /*
         * SETTERS
         */

        Container &layout(Layout layout) {
            lv_cont_set_layout(raw(), static_cast<lv_layout_t>(layout));
            return this->underlying();
        }

        Container &fit4(Fit left, Fit right, Fit top, Fit bottom) {
            lv_cont_set_fit4(raw(), static_cast<lv_fit_t>(left), static_cast<lv_fit_t>(right),
                             static_cast<lv_fit_t>(top), static_cast<lv_fit_t>(bottom));
            return this->underlying();
        }

        Container &fit2(Fit hor, Fit ver) {
            lv_cont_set_fit2(raw(), static_cast<lv_fit_t>(hor), static_cast<lv_fit_t>(ver));
            return this->underlying();
        }

        Container &fit(Fit fit) {
            lv_cont_set_fit(raw(), static_cast<lv_fit_t>(fit));
            return this->underlying();
        }

        /*
         * GETTERS
         */

        [[nodiscard]] lv_layout_t layout() const {
            return lv_cont_get_layout(raw());
        }

        [[nodiscard]] Fit fit_left() const {
            return static_cast<Fit>(lv_cont_get_fit_left(raw()));
        }

        [[nodiscard]] Fit fit_right() const {
            return static_cast<Fit>(lv_cont_get_fit_right(raw()));
        }

        [[nodiscard]] Fit fit_top() const {
            return static_cast<Fit>(lv_cont_get_fit_top(raw()));
        }

        [[nodiscard]] Fit fit_bottom() const {
            return static_cast<Fit>(lv_cont_get_fit_bottom(raw()));
        }

    };
}

#endif // LV_USE_CONT
