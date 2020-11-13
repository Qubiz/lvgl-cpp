#pragma once

#include "Object.h"

#if LV_USE_WIN && LV_USE_BTN && LV_USE_LABEL && LV_USE_IMG && LV_USE_PAGE

namespace lvglcpp {

    enum class WindowPart {
        BG = LV_WIN_PART_BG, /**< Window object background style. */
        HEADER = LV_WIN_PART_HEADER, /**< Window titlebar background style. */
        CONTENT_SCROLLABLE = LV_WIN_PART_CONTENT_SCROLLABLE, /**< Window content style. */
        SCROLLBAR = LV_WIN_PART_SCROLLBAR /**< Window scrollbar style. */
    };

    class Window : public Object<Window> {
    protected:
        explicit Window(lv_obj_t *other) noexcept: Object(other) {};

    public:

        Window() noexcept: Object(lv_win_create(lv_scr_act(), nullptr)) {};

        template<typename T>
        explicit Window(const Object <T> &parent) noexcept
                : Object(lv_win_create(parent.raw(), nullptr)) {}

        template<typename T>
        explicit Window(const Object <T> &parent, const Window &copy) noexcept
                : Object(lv_win_create(parent.raw(), copy.raw())) {}

        void clean() {
            return lv_win_clean(raw());
        }

        Button add_btn_right(const void *img_src) {
            return Button(lv_win_add_btn_right(raw(), img_src));
        }

        Button add_btn_left(const void *img_src) {
            return Button(lv_win_add_btn_left(raw(), img_src));
        }

        /*
         * SETTERS
         */
        static void close_event_cb(Button &close_button, lv_event_t event) {
            lv_win_close_event_cb(close_button.raw(), event);
        }

        Window &title(const char *title) {
            lv_win_set_title(raw(), title);
            return this->underlying();
        }

        Window &header_height(lv_coord_t size) {
            lv_win_set_header_height(raw(), size);
            return this->underlying();
        }

        Window &btn_width(lv_coord_t width) {
            lv_win_set_btn_width(raw(), width);
            return this->underlying();
        }

        Window &content_size(lv_coord_t w, lv_coord_t h) {
            lv_win_set_content_size(raw(), w, h);
            return this->underlying();
        }

        Window &layout(Layout layout) {
            lv_win_set_layout(raw(), static_cast<lv_layout_t>(layout));
            return this->underlying();
        }

        Window &scrollbar_mode(ScrollbarMode sb_mode) {
            lv_win_set_scrollbar_mode(raw(), static_cast<lv_scrollbar_mode_t>(sb_mode));
            return this->underlying();
        }

        Window &anim_time(uint16_t anim_time) {
            lv_win_set_anim_time(raw(), anim_time);
            return this->underlying();
        }

        Window &draggable(bool en) {
            lv_win_set_drag(raw(), en);
            return this->underlying();
        }

        /*
         * GETTERS
         */
        [[nodiscard]] const char *title() const {
            return lv_win_get_title(raw());
        }

        [[nodiscard]] lv_obj_t *content() const {
            return lv_win_get_content(raw());
        }

        [[nodiscard]] lv_coord_t header_height() const {
            return lv_win_get_header_height(raw());
        }

        [[nodiscard]] lv_coord_t btn_width() const {
            return lv_win_get_btn_width(raw());
        }

        static Window from_btn(Button &button) {
            return Window(lv_win_get_from_btn(button.raw()));
        }

        [[nodiscard]] lv_layout_t layout() const {
            return lv_win_get_layout(raw());
        }

        [[nodiscard]] lv_scrollbar_mode_t sb_mode() const {
            return lv_win_get_sb_mode(raw());
        }

        [[nodiscard]] uint16_t anim_time() const {
            return lv_win_get_anim_time(raw());
        }

        [[nodiscard]] lv_coord_t content_width() const {
            return lv_win_get_width(raw());
        }

        [[nodiscard]] bool draggable() const {
            return lv_win_get_drag(raw());
        }


        /*
         * OTHER
         */
        void focus(lv_obj_t *obj, lv_anim_enable_t anim_en) {
            return lv_win_focus(raw(), obj, anim_en);
        }

        void scroll_hor(lv_coord_t dist) {
            return lv_win_scroll_hor(raw(), dist);
        }

        void scroll_ver(lv_coord_t dist) {
            return lv_win_scroll_ver(raw(), dist);
        }

    };
}

#endif // LV_USE_WIN