#pragma once

#include "Object.h"

#if LV_USE_TEXTAREA && LV_USE_PAGE && LV_USE_LABEL

namespace lvglcpp {

    enum class TextarePart : lv_textarea_style_t {
        BG = LV_TEXTAREA_PART_BG, /**< Text area background style */
        SCROLLBAR = LV_TEXTAREA_PART_SCROLLBAR, /**< Scrollbar style */
        EDGE_FLASH = LV_TEXTAREA_PART_EDGE_FLASH, /**< Edge flash style */
        CURSOR = LV_TEXTAREA_PART_CURSOR, /**< Cursor style */
        PLACEHOLDER = LV_TEXTAREA_PART_PLACEHOLDER, /**< Placeholder style */
    };

    class Textarea : public Object<Textarea> {
    protected:
        explicit Textarea(lv_obj_t *other) noexcept: Object(other) {};

    public:

        Textarea() noexcept: Object(lv_textarea_create(lv_scr_act(), nullptr)) {};

        template<typename T>
        explicit Textarea(const Object<T> &parent) noexcept
                : Object(lv_textarea_create(parent.raw(), nullptr)) {}

        template<typename T>
        explicit Textarea(const Object<T> &parent, const Textarea &copy) noexcept
                : Object(lv_textarea_create(parent.raw(), copy.raw())) {}

        Textarea &add_char(uint32_t c) {
            lv_textarea_add_char(raw(), c);
            return this->underlying();
        }

        Textarea &add_text(const char *txt) {
            lv_textarea_add_text(raw(), txt);
            return this->underlying();
        }

        Textarea &del_char(lv_obj_t *ta) {
            lv_textarea_del_char(raw());
            return this->underlying();
        }

        Textarea &del_char_forward() {
            lv_textarea_del_char_forward(raw());
            return this->underlying();
        }

        /*
         * SETTERS
         */


        Textarea &text(const char *txt) {
            lv_textarea_set_text(raw(), txt);
            return this->underlying();
        }


        Textarea &placeholder_text(const char *txt) {
            lv_textarea_set_placeholder_text(raw(), txt);
            return this->underlying();
        }


        Textarea &cursor_pos(int32_t pos) {
            lv_textarea_set_cursor_pos(raw(), pos);
            return this->underlying();
        }


        Textarea &cursor_hidden(bool hide) {
            lv_textarea_set_cursor_hidden(raw(), hide);
            return this->underlying();
        }


        Textarea &cursor_click_pos(bool en) {
            lv_textarea_set_cursor_click_pos(raw(), en);
            return this->underlying();
        }


        Textarea &pwd_mode(bool en) {
            lv_textarea_set_pwd_mode(raw(), en);
            return this->underlying();
        }


        Textarea &one_line(bool en) {
            lv_textarea_set_one_line(raw(), en);
            return this->underlying();
        }


        Textarea &text_align(LabelAlign align) {
            lv_textarea_set_text_align(raw(), static_cast<lv_label_align_t>(align));
            return this->underlying();
        }


        Textarea &accepted_chars(const char *list) {
            lv_textarea_set_accepted_chars(raw(), list);
            return this->underlying();
        }


        Textarea &max_length(uint32_t num) {
            lv_textarea_set_max_length(raw(), num);
            return this->underlying();
        }


        Textarea &insert_replace(const char *txt) {
            lv_textarea_set_insert_replace(raw(), txt);
            return this->underlying();
        }

        Textarea &scrollbar_mode(ScrollbarMode mode) {
            lv_textarea_set_scrollbar_mode(raw(), static_cast<lv_scrollbar_mode_t>(mode));
            return this->underlying();
        }


        Textarea &scroll_propagation(bool en) {
            lv_textarea_set_scroll_propagation(raw(), en);
            return this->underlying();
        }


        Textarea &edge_flash(bool en) {
            lv_textarea_set_edge_flash(raw(), en);
            return this->underlying();
        }

        Textarea &text_sel(bool en) {
            lv_textarea_set_text_sel(raw(), en);
            return this->underlying();
        }


        Textarea &pwd_show_time(uint16_t time) {
            lv_textarea_set_pwd_show_time(raw(), time);
            return this->underlying();
        }

        Textarea &cursor_blink_time(uint16_t time) {
            lv_textarea_set_cursor_blink_time(raw(), time);
            return this->underlying();
        }

        /*
         * GETTERS
         */

        [[nodiscard]] const char *text() const {
            return lv_textarea_get_text(raw());
        }

        [[nodiscard]] const char *placeholder_text() const {
            return lv_textarea_get_placeholder_text(raw());
        }

        [[nodiscard]] lv_obj_t *label() const {
            return lv_textarea_get_label(raw());
        }

        [[nodiscard]] uint32_t cursor_pos() const {
            return lv_textarea_get_cursor_pos(raw());
        }

        [[nodiscard]] bool cursor_hidden() const {
            return lv_textarea_get_cursor_hidden(raw());
        }

        [[nodiscard]] bool cursor_click_pos() const {
            return lv_textarea_get_cursor_click_pos(raw());
        }

        [[nodiscard]] bool pwd_mode() const {
            return lv_textarea_get_pwd_mode(raw());
        }

        [[nodiscard]] bool one_line() const {
            return lv_textarea_get_one_line(raw());
        }

        [[nodiscard]] const char *accepted_chars() const {
            return lv_textarea_get_accepted_chars(raw());
        }

        [[nodiscard]] uint32_t max_length() const {
            return lv_textarea_get_max_length(raw());
        }

        [[nodiscard]] lv_scrollbar_mode_t scrollbar_mode() const {
            return lv_textarea_get_scrollbar_mode(raw());
        }

        [[nodiscard]] bool scroll_propagation() const {
            return lv_textarea_get_scroll_propagation(raw());
        }

        [[nodiscard]] bool edge_flash() const {
            return lv_textarea_get_edge_flash(raw());
        }

        [[nodiscard]] bool selected() const {
            return lv_textarea_text_is_selected(raw());
        }

        [[nodiscard]] bool text_sel_en() const {
            return lv_textarea_get_text_sel_en(raw());
        }

        [[nodiscard]] uint16_t pwd_show_time() const {
            return lv_textarea_get_pwd_show_time(raw());
        }

        [[nodiscard]] uint16_t cursor_blink_time() const {
            return lv_textarea_get_cursor_blink_time(raw());
        }

        /*
         * GETTERS
         */
        void clear_selection() {
            return lv_textarea_clear_selection(raw());
        }

        void cursor_right() {
            return lv_textarea_cursor_right(raw());
        }

        void cursor_left() {
            return lv_textarea_cursor_left(raw());
        }

        void cursor_down() {
            return lv_textarea_cursor_down(raw());
        }

        void cursor_up() {
            return lv_textarea_cursor_up(raw());
        }

    };
}

#endif // LV_USE_TEXTAREA