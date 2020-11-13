#pragma once

#include "Object.h"

#if LV_USE_LIST && \
    LV_USE_PAGE && \
    LV_USE_BTN && \
    LV_USE_LABEL

#include <optional>

#include "Page.h"

namespace lvglcpp {

    enum class ListPart : lv_list_style_t {
        BG = LV_LIST_PART_BG,
        SCROLLBAR = LV_LIST_PART_SCROLLBAR,
        EDGE_FLASH = LV_LIST_PART_EDGE_FLASH,
        SCROLLABLE = LV_LIST_PART_SCROLLABLE,
    };

    class List : public Object<List> {
    protected:
        explicit List(lv_obj_t *other) noexcept: Object(other) {};

    public:

        List() noexcept: Object(lv_list_create(lv_scr_act(), nullptr)) {};

        template<typename T>
        explicit List(const Object<T> &parent) noexcept
                : Object(lv_list_create(parent.raw(), nullptr)) {}

        template<typename T>
        explicit List(const Object<T> &parent, const List &copy) noexcept
                : Object(lv_list_create(parent.raw(), copy.raw())) {}

        /*
         * SETTERS
         */
        void clean() {
            lv_list_clean(raw());
        }

        Button add_btn(const void *img_src = nullptr, const char *txt = nullptr) {
            return Button(lv_list_add_btn(raw(), img_src, txt));
        }

        [[nodiscard]] bool remove(uint16_t index) const {
            return lv_list_remove(raw(), index);
        }

        List &focus_btn(Button &btn) {
            lv_list_focus_btn(raw(), btn.raw());
            return this->underlying();
        }

        List &scrollbar_mode(ScrollbarMode mode) {
            lv_list_set_scrollbar_mode(raw(), static_cast<lv_scrollbar_mode_t>(mode));
            return this->underlying();
        }

        List &scroll_propagation(bool en) {
            lv_list_set_scroll_propagation(raw(), en);
            return this->underlying();
        }

        List &edge_flash(bool en) {
            lv_list_set_edge_flash(raw(), en);
            return this->underlying();
        }

        List &anim_time(uint16_t anim_time) {
            lv_list_set_anim_time(raw(), anim_time);
            return this->underlying();
        }

        List &layout(lv_layout_t layout) {
            lv_list_set_layout(raw(), layout);
            return this->underlying();
        }

        /*
         * GETTERS
         */

        [[nodiscard]] const char *btn_text() const {
            return lv_list_get_btn_text(raw());
        }

        [[nodiscard]] Label btn_label() const {
            return Label(lv_list_get_btn_label(raw()));
        }

        [[nodiscard]] Image btn_img() const {
            return Image(lv_list_get_btn_img(raw()));
        }

        [[nodiscard]] std::optional<Button> prev_btn(Button &current) const {
            auto prev = lv_list_get_prev_btn(raw(), current.raw());
            return prev != nullptr ? std::optional<Button>(Button(prev)) : std::nullopt;
        }

        [[nodiscard]] std::optional<Button> next_btn(Button &current) const {
            auto prev = lv_list_get_next_btn(raw(), current.raw());
            return prev != nullptr ? std::optional<Button>(Button(prev)) : std::nullopt;
        }

        [[nodiscard]] int32_t btn_index(Button &current) const {
            return lv_list_get_btn_index(raw(), current.raw());
        }

        [[nodiscard]] uint16_t size() const {
            return lv_list_get_size(raw());
        }

#if LV_USE_GROUP

        [[nodiscard]] Button btn_selected() const {
            return Button(lv_list_get_btn_selected(raw()));
        }

#endif

        [[nodiscard]] lv_layout_t layout() const {
            return lv_list_get_layout(raw());
        }

        [[nodiscard]] ScrollbarMode scrollbar_mode() const {
            return static_cast<ScrollbarMode>(lv_list_get_scrollbar_mode(raw()));
        }

        [[nodiscard]] bool scroll_propagation() const {
            return lv_list_get_scroll_propagation(raw());
        }

        [[nodiscard]] bool edge_flash() const {
            return lv_list_get_edge_flash(raw());
        }

        [[nodiscard]] uint16_t anim_time() const {
            return lv_list_get_anim_time(raw());
        }

        /*
         * OTHER
         */

        void up() {
            lv_list_up(raw());
        }

        void down() {
            lv_list_down(raw());
        }

        static void focus(const Button &button, lv_anim_enable_t anim = LV_ANIM_OFF) {
            lv_list_focus(button.raw(), anim);
        }

    };
}

#endif // LV_USE_LIST