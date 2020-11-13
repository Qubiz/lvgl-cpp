#pragma once

#include "Object.h"

#if LV_USE_PAGE

namespace lvglcpp {

    enum class ScrollbarMode : lv_scrollbar_mode_t {
        OFF = LV_SCROLLBAR_MODE_OFF, /**< Never show scroll bars*/
        ON = LV_SCROLLBAR_MODE_ON, /**< Always show scroll bars*/
        DRAG = LV_SCROLLBAR_MODE_DRAG, /**< Show scroll bars when page is being dragged*/
        AUTO = LV_SCROLLBAR_MODE_AUTO, /**< Show scroll bars when the scrollable container is large enough to be scrolled*/
        HIDE = LV_SCROLLBAR_MODE_HIDE, /**< Hide the scroll bar temporally*/
        UNHIDE = LV_SCROLLBAR_MODE_UNHIDE, /**< Unhide the previously hidden scroll bar. Recover original mode too*/
    };

    enum class PageEdge : lv_page_edge_t {
        LEFT = LV_PAGE_EDGE_LEFT,
        TOP = LV_PAGE_EDGE_TOP,
        RIGHT = LV_PAGE_EDGE_RIGHT,
        BOTTOM = LV_PAGE_EDGE_BOTTOM
    };

    enum class PagePart : lv_part_style_t {
        BG = LV_PAGE_PART_BG,
        SCROLLBAR = LV_PAGE_PART_SCROLLBAR,
        EDGE_FLASH = LV_PAGE_PART_EDGE_FLASH,
        SCROLLABLE = LV_PAGE_PART_SCROLLABLE,
    };

    class Page : public Object<Page> {
    protected:
        explicit Page(lv_obj_t *other) noexcept: Object(other) {};

        friend class Tabview;

    public:

        Page() noexcept: Object(lv_page_create(lv_scr_act(), nullptr)) {};

        template<typename T>
        explicit Page(const Object <T> &parent) noexcept
                : Object(lv_page_create(parent.raw(), nullptr)) {}

        template<typename T>
        explicit Page(const Object <T> &parent, const Page &copy) noexcept
                : Object(lv_page_create(parent.raw(), copy.raw())) {}

        void clean() {
            lv_page_clean(raw());
        }

        /*
         * SETTERS
         */

        [[nodiscard]] Object<> scrollable() const {
            return Object<>(lv_page_get_scrollable(raw()));
        }

        [[nodiscard]] uint16_t anim_time() const {
            return lv_page_get_anim_time(raw());
        }

        Page &scrollbar_mode(ScrollbarMode mode) {
            lv_page_set_scrollbar_mode(raw(), static_cast<lv_scrollbar_mode_t>(mode));
            return this->underlying();
        }

        Page &anim_time(uint16_t anim_time) {
            lv_page_set_anim_time(raw(), anim_time);
            return this->underlying();
        }

        Page &scroll_propagation(bool enabled) {
            lv_page_set_scroll_propagation(raw(), enabled);
            return this->underlying();
        };

        Page &edge_flash(bool enabled) {
            lv_page_set_edge_flash(raw(), enabled);
            return this->underlying();
        };

        Page &scrollable_fit4(lv_fit_t left, lv_fit_t right, lv_fit_t top, lv_fit_t bottom) {
            lv_page_set_scrollable_fit4(raw(), left, right, top, bottom);
            return this->underlying();
        }

        Page &scrollable_fit2(lv_fit_t hor, lv_fit_t ver) {
            lv_page_set_scrollable_fit2(raw(), hor, ver);
            return this->underlying();
        }

        Page &scrollable_fit(lv_fit_t fit) {
            lv_page_set_scrollable_fit(raw(), fit);
            return this->underlying();
        }

        Page &scrl_width(lv_coord_t w) {
            lv_page_set_scrl_width(raw(), w);
            return this->underlying();
        }

        Page &scrl_height(lv_coord_t h) {
            lv_page_set_scrl_height(raw(), h);
            return this->underlying();
        }

        Page &scrl_layout(lv_layout_t layout) {
            lv_page_set_scrl_layout(raw(), layout);
            return this->underlying();
        }

        /*
         * GETTERS
         */

        [[nodiscard]] lv_scrollbar_mode_t scrollbar_mode() const {
            return lv_page_get_scrollbar_mode(raw());
        }

        [[nodiscard]] bool scroll_propagation() const {
            return lv_page_get_scroll_propagation(raw());
        }

        [[nodiscard]] bool edge_flash() const {
            return lv_page_get_edge_flash(raw());
        }

        [[nodiscard]] lv_coord_t page_width_fit() const {
            return lv_page_get_width_fit(raw());
        }

        [[nodiscard]] lv_coord_t page_height_fit() const {
            return lv_page_get_height_fit(raw());
        }

        [[nodiscard]] lv_coord_t width_grid(uint8_t div, uint8_t span) const {
            return lv_page_get_width_grid(raw(), div, span);
        }

        [[nodiscard]] lv_coord_t height_grid(uint8_t div, uint8_t span) const {
            return lv_page_get_height_grid(raw(), div, span);
        }

        [[nodiscard]] lv_coord_t scrl_width() const {
            return lv_page_get_scrl_width(raw());
        }

        [[nodiscard]] lv_coord_t scrl_height() const {
            return lv_page_get_scrl_height(raw());
        }

        [[nodiscard]] lv_layout_t layout() const {
            return lv_page_get_scrl_layout(raw());
        }

        [[nodiscard]] lv_fit_t fit_left() const {
            return lv_page_get_scrl_fit_left(raw());
        }

        [[nodiscard]] lv_fit_t fit_right() const {
            return lv_page_get_scrl_fit_right(raw());
        }

        [[nodiscard]] lv_fit_t fit_top() const {
            return lv_page_get_scrl_fit_top(raw());
        }

        [[nodiscard]] lv_fit_t fit_bottom() const {
            return lv_page_get_scrl_fit_bottom(raw());
        }

        /*
         * OTHER
         */

        [[nodiscard]] bool on_edge(PageEdge edge) const {
            return lv_page_on_edge(raw(), static_cast<lv_page_edge_t>(edge));
        }

        void glue_obj(bool glue) {
            return lv_page_glue_obj(raw(), glue);
        }

        template<typename ObjectType>
        void focus(const ObjectType &obj, lv_anim_enable_t anim_en) {
            return lv_page_focus(raw(), obj.raw(), anim_en);
        }

        void scroll_hor(lv_coord_t dist) {
            return lv_page_scroll_hor(raw(), dist);
        }

        void scroll_ver(lv_coord_t dist) {
            return lv_page_scroll_ver(raw(), dist);
        }

        void start_edge_flash(lv_page_edge_t edge) {
            return lv_page_start_edge_flash(raw(), edge);
        }

    };
}

#endif // LV_USE_PAGE