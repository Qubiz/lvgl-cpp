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

    class MessageBox final : public Object<MessageBox> {
    public:

        MessageBox() : Object(lv_msgbox_create(lv_scr_act(), nullptr)) {}

        MessageBox &add_btns(std::span<const char *> actions_map) {
            lv_msgbox_add_btns(get(), const_cast<const char **>(actions_map.data()));
            return this->underlying();
        }

        /*
         * SETTERS
         */
        MessageBox &text(const char *txt) {
            lv_msgbox_set_text(get(), txt);
            return this->underlying();
        }

        MessageBox &anim_time(uint16_t anim_time) {
            lv_msgbox_set_anim_time(get(), anim_time);
            return this->underlying();
        }

        MessageBox &start_auto_close(uint16_t delay) {
            lv_msgbox_start_auto_close(get(), delay);
            return this->underlying();
        }

        MessageBox &stop_auto_close() {
            lv_msgbox_stop_auto_close(get());
            return this->underlying();
        }

        MessageBox &recolor(bool en) {
            lv_msgbox_set_recolor(get(), en);
            return this->underlying();
        }

        /*
         * GETTERS
         */

        [[nodiscard]] const char *text() const {
            return lv_msgbox_get_text(get());
        }

        [[nodiscard]] uint16_t active_btn() const {
            return lv_msgbox_get_active_btn(get());
        }

        [[nodiscard]] const char *active_btn_text() const {
            return lv_msgbox_get_active_btn_text(get());
        }

        [[nodiscard]] uint16_t anim_time() const {
            return lv_msgbox_get_anim_time(get());
        }

        [[nodiscard]] bool recolor() const {
            return lv_msgbox_get_recolor(get());
        }

        [[nodiscard]] lv_obj_t *btnmatrix() const {
            return lv_msgbox_get_btnmatrix(get());
        }

    };
}

#endif // LV_USE_MSGBOX