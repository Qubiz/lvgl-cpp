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

    class Page final : public Object<Page> {
    protected:
        explicit Page(lv_obj_t *other) noexcept: Object(other) {};

        friend class Tabview;

    public:

        Page() noexcept: Object(lv_page_create(lv_scr_act(), nullptr)) {};

        explicit Page(const Object<> &parent) noexcept
                : Object(lv_page_create(parent.get(), nullptr)) {}

        explicit Page(const Object<> &parent, const Page &copy) noexcept
                : Object(lv_page_create(parent.get(), copy.get())) {}

        void clean() {
            lv_page_clean(get());
        }

        /*
         * SETTERS
         */

        [[nodiscard]] Object<> scrollable() const {
            return Object<>(lv_page_get_scrollable(get()));
        }

        [[nodiscard]] uint16_t anim_time() const {
            return lv_page_get_anim_time(get());
        }

        Page &scrollbar_mode(ScrollbarMode mode) {
            lv_page_set_scrollbar_mode(get(), static_cast<lv_scrollbar_mode_t>(mode));
            return this->underlying();
        }

        Page &anim_time(uint16_t anim_time) {
            lv_page_set_anim_time(get(), anim_time);
            return this->underlying();
        }

        Page &scroll_propagation(bool enabled) {
            lv_page_set_scroll_propagation(get(), enabled);
            return this->underlying();
        };

        Page &edge_flash(bool enabled) {
            lv_page_set_edge_flash(get(), enabled);
            return this->underlying();
        };

        Page &scrollable_fit4(lv_fit_t left, lv_fit_t right, lv_fit_t top, lv_fit_t bottom) {
            lv_page_set_scrollable_fit4(get(), left, right, top, bottom);
            return this->underlying();
        }

        Page &scrollable_fit2(lv_fit_t hor, lv_fit_t ver) {
            lv_page_set_scrollable_fit2(get(), hor, ver);
            return this->underlying();
        }

        Page &scrollable_fit(lv_fit_t fit) {
            lv_page_set_scrollable_fit(get(), fit);
            return this->underlying();
        }

        Page &scrl_width(lv_coord_t w) {
            lv_page_set_scrl_width(get(), w);
            return this->underlying();
        }

        Page &scrl_height(lv_coord_t h) {
            lv_page_set_scrl_height(get(), h);
            return this->underlying();
        }

        Page &scrl_layout(lv_layout_t layout) {
            lv_page_set_scrl_layout(get(), layout);
            return this->underlying();
        }

        /*
         * GETTERS
         */

        [[nodiscard]] lv_scrollbar_mode_t scrollbar_mode() const {
            return lv_page_get_scrollbar_mode(get());
        }
        [[nodiscard]] bool scroll_propagation() const {
            return lv_page_get_scroll_propagation(get());
        }
        [[nodiscard]] bool edge_flash() const {
            return lv_page_get_edge_flash(get());
        }
        [[nodiscard]] lv_coord_t page_width_fit() const {
            return lv_page_get_width_fit(get());
        }
        [[nodiscard]] lv_coord_t page_height_fit() const {
            return lv_page_get_height_fit(get());
        }
        [[nodiscard]] lv_coord_t width_grid(uint8_t div, uint8_t span) const {
            return lv_page_get_width_grid(get(), div, span);
        }
        [[nodiscard]] lv_coord_t height_grid(uint8_t div, uint8_t span) const {
            return lv_page_get_height_grid(get(), div, span);
        }
        
        [[nodiscard]] lv_coord_t scrl_width() const {
            return lv_page_get_scrl_width(get());
        }
        [[nodiscard]] lv_coord_t scrl_height() const {
            return lv_page_get_scrl_height(get());
        }
        [[nodiscard]] lv_layout_t layout() const {
            return lv_page_get_scrl_layout(get());
        }
        [[nodiscard]] lv_fit_t fit_left() const {
            return lv_page_get_scrl_fit_left(get());
        }
        [[nodiscard]] lv_fit_t fit_right() const {
            return lv_page_get_scrl_fit_right(get());
        }
        [[nodiscard]] lv_fit_t fit_top() const {
            return lv_page_get_scrl_fit_top(get());
        }
        [[nodiscard]] lv_fit_t fit_bottom() const {
            return lv_page_get_scrl_fit_bottom(get());
        }

        /*
         * OTHER
         */

        [[nodiscard]] bool on_edge(PageEdge edge) const {
            return lv_page_on_edge(get(), static_cast<lv_page_edge_t>(edge));
        }
        void glue_obj(bool glue) {
            return lv_page_glue_obj(get(), glue);
        }

        template<typename ObjectType>
        void focus(const ObjectType& obj, lv_anim_enable_t anim_en) {
            return lv_page_focus(get(), obj.get(), anim_en);
        }
        void scroll_hor(lv_coord_t dist) {
            return lv_page_scroll_hor(get(), dist);
        }
        void scroll_ver(lv_coord_t dist) {
            return lv_page_scroll_ver(get(), dist);
        }
        void start_edge_flash(lv_page_edge_t edge) {
            return lv_page_start_edge_flash(get(), edge);
        }

    };
}

#endif // LV_USE_PAGE