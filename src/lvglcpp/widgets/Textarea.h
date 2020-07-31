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

    class Textarea final : public Object<Textarea> {
    protected:
        explicit Textarea(lv_obj_t *other) noexcept: Object(other) {};

    public:

        Textarea() noexcept: Object(lv_textarea_create(lv_scr_act(), nullptr)) {};

        explicit Textarea(const Object<> &parent) noexcept
                : Object(lv_textarea_create(parent.get(), nullptr)) {}

        explicit Textarea(const Object<> &parent, const Textarea &copy) noexcept
                : Object(lv_textarea_create(parent.get(), copy.get())) {}

        Textarea &add_char(uint32_t c) {
            lv_textarea_add_char(get(), c);
            return this->underlying();
        }

        Textarea &add_text(const char *txt) {
            lv_textarea_add_text(get(), txt);
            return this->underlying();
        }

        Textarea &del_char(lv_obj_t *ta) {
            lv_textarea_del_char(get());
            return this->underlying();
        }

        Textarea &del_char_forward() {
            lv_textarea_del_char_forward(get());
            return this->underlying();
        }

        /*
         * SETTERS
         */


        Textarea &text(const char *txt) {
            lv_textarea_set_text(get(), txt);
            return this->underlying();
        }


        Textarea &placeholder_text(const char *txt) {
            lv_textarea_set_placeholder_text(get(), txt);
            return this->underlying();
        }


        Textarea &cursor_pos(int32_t pos) {
            lv_textarea_set_cursor_pos(get(), pos);
            return this->underlying();
        }


        Textarea &cursor_hidden(bool hide) {
            lv_textarea_set_cursor_hidden(get(), hide);
            return this->underlying();
        }


        Textarea &cursor_click_pos(bool en) {
            lv_textarea_set_cursor_click_pos(get(), en);
            return this->underlying();
        }


        Textarea &pwd_mode(bool en) {
            lv_textarea_set_pwd_mode(get(), en);
            return this->underlying();
        }


        Textarea &one_line(bool en) {
            lv_textarea_set_one_line(get(), en);
            return this->underlying();
        }


        Textarea &text_align(LabelAlign align) {
            lv_textarea_set_text_align(get(), static_cast<lv_label_align_t>(align));
            return this->underlying();
        }


        Textarea &accepted_chars(const char *list) {
            lv_textarea_set_accepted_chars(get(), list);
            return this->underlying();
        }


        Textarea &max_length(uint32_t num) {
            lv_textarea_set_max_length(get(), num);
            return this->underlying();
        }


        Textarea &insert_replace(const char *txt) {
            lv_textarea_set_insert_replace(get(), txt);
            return this->underlying();
        }

        Textarea &sscrollbar_mode(ScrollbarMode mode) {
            lv_textarea_set_sscrollbar_mode(get(), static_cast<lv_scrollbar_mode_t>(mode));
            return this->underlying();
        }


        Textarea &scroll_propagation(bool en) {
            lv_textarea_set_scroll_propagation(get(), en);
            return this->underlying();
        }


        Textarea &edge_flash(bool en) {
            lv_textarea_set_edge_flash(get(), en);
            return this->underlying();
        }

        Textarea &text_sel(bool en) {
            lv_textarea_set_text_sel(get(), en);
            return this->underlying();
        }


        Textarea &pwd_show_time(uint16_t time) {
            lv_textarea_set_pwd_show_time(get(), time);
            return this->underlying();
        }

        Textarea &cursor_blink_time(uint16_t time) {
            lv_textarea_set_cursor_blink_time(get(), time);
            return this->underlying();
        }
        
        /*
         * GETTERS
         */

        [[nodiscard]] const char * text() const {
            return lv_textarea_get_text(get());
        }
        [[nodiscard]] const char * placeholder_text() const {
            return lv_textarea_get_placeholder_text(get());
        }
        [[nodiscard]] lv_obj_t * label() const {
            return lv_textarea_get_label(get());
        }
        [[nodiscard]] uint32_t cursor_pos() const {
            return lv_textarea_get_cursor_pos(get());
        }
        [[nodiscard]] bool cursor_hidden() const {
            return lv_textarea_get_cursor_hidden(get());
        }
        [[nodiscard]] bool cursor_click_pos() const {
            return lv_textarea_get_cursor_click_pos(get());
        }
        [[nodiscard]] bool pwd_mode() const {
            return lv_textarea_get_pwd_mode(get());
        }
        [[nodiscard]] bool one_line() const {
            return lv_textarea_get_one_line(get());
        }
        [[nodiscard]] const char * accepted_chars() const {
            return lv_textarea_get_accepted_chars(get());
        }
        [[nodiscard]] uint32_t max_length() const {
            return lv_textarea_get_max_length(get());
        }

        [[nodiscard]] lv_scrollbar_mode_t scrollbar_mode() const {
            return lv_textarea_get_scrollbar_mode(get());
        }
        [[nodiscard]] bool scroll_propagation() const {
            return lv_textarea_get_scroll_propagation(get());
        }
        [[nodiscard]] bool edge_flash() const {
            return lv_textarea_get_edge_flash(get());
        }
        [[nodiscard]] bool selected() const {
            return lv_textarea_text_is_selected(get());
        }
        [[nodiscard]] bool text_sel_en() const {
            return lv_textarea_get_text_sel_en(get());
        }
        [[nodiscard]] uint16_t pwd_show_time() const {
            return lv_textarea_get_pwd_show_time(get());
        }
        [[nodiscard]] uint16_t cursor_blink_time() const {
            return lv_textarea_get_cursor_blink_time(get());
        }

        /*
         * GETTERS
         */
        void clear_selection() {
            return lv_textarea_clear_selection(get());
        }
        void cursor_right() {
            return lv_textarea_cursor_right(get());
        }
        void cursor_left() {
            return lv_textarea_cursor_left(get());
        }
        void cursor_down() {
            return lv_textarea_cursor_down(get());
        }
        void cursor_up() {
            return lv_textarea_cursor_up(get());
        }

    };
}

#endif // LV_USE_TEXTAREA