#pragma once

#include "Object.h"

#if LV_USE_MSGBOX && \
    LV_USE_CONT && \
    LV_USE_BTNMATRIX && \
    LV_USE_LABEL

namespace lvglcpp {

    enum class MessageBoxPart : lv_msgbox_style_t {
        BG = LV_MSGBOX_PART_BG,
        BTN_BG = LV_MSGBOX_PART_BTN_BG,
        BTN = LV_MSGBOX_PART_BTN,
    };

    class MessageBox : public Object<MessageBox> {
    protected:
        explicit MessageBox(lv_obj_t *other) noexcept: Object(other) {};

    public:

        MessageBox() noexcept: Object(lv_msgbox_create(lv_scr_act(), nullptr)) {};

        template<typename T>
        explicit MessageBox(const Object<T> &parent) noexcept
                : Object(lv_msgbox_create(parent.raw(), nullptr)) {}

        template<typename T>
        explicit MessageBox(const Object<T> &parent, const MessageBox &copy) noexcept
                : Object(lv_msgbox_create(parent.raw(), copy.raw())) {}

        MessageBox &add_btns(std::span<const char *> actions_map) {
            lv_msgbox_add_btns(raw(), const_cast<const char **>(actions_map.data()));
            return this->underlying();
        }

        /*
         * SETTERS
         */
        MessageBox &text(const char *txt) {
            lv_msgbox_set_text(raw(), txt);
            return this->underlying();
        }

        MessageBox &anim_time(uint16_t anim_time) {
            lv_msgbox_set_anim_time(raw(), anim_time);
            return this->underlying();
        }

        MessageBox &start_auto_close(uint16_t delay) {
            lv_msgbox_start_auto_close(raw(), delay);
            return this->underlying();
        }

        MessageBox &stop_auto_close() {
            lv_msgbox_stop_auto_close(raw());
            return this->underlying();
        }

        MessageBox &recolor(bool en) {
            lv_msgbox_set_recolor(raw(), en);
            return this->underlying();
        }

        /*
         * GETTERS
         */

        [[nodiscard]] const char *text() const {
            return lv_msgbox_get_text(raw());
        }

        [[nodiscard]] uint16_t active_btn() const {
            return lv_msgbox_get_active_btn(raw());
        }

        [[nodiscard]] const char *active_btn_text() const {
            return lv_msgbox_get_active_btn_text(raw());
        }

        [[nodiscard]] uint16_t anim_time() const {
            return lv_msgbox_get_anim_time(raw());
        }

        [[nodiscard]] bool recolor() const {
            return lv_msgbox_get_recolor(raw());
        }

        [[nodiscard]] lv_obj_t *btnmatrix() const {
            return lv_msgbox_get_btnmatrix(raw());
        }

    };
}

#endif // LV_USE_MSGBOX