#pragma once

#include "Object.h"

#if LV_USE_TABVIEW && LV_USE_BTNMATRIX && LV_USE_PAGE

namespace lvglcpp {

    enum class TabviewButtonsPosition : lv_tabview_btns_pos_t {
        NONE = LV_TABVIEW_TAB_POS_NONE,
        TOP = LV_TABVIEW_TAB_POS_TOP,
        BOTTOM = LV_TABVIEW_TAB_POS_BOTTOM,
        LEFT = LV_TABVIEW_TAB_POS_LEFT,
        RIGHT = LV_TABVIEW_TAB_POS_RIGHT
    };

    enum class TabviewPart : lv_tabview_part_t {
        BG = LV_TABVIEW_PART_BG,
        BG_SCRLLABLE = LV_TABVIEW_PART_BG_SCRLLABLE,
        TAB_BG = LV_TABVIEW_PART_TAB_BG,
        TAB_BTN = LV_TABVIEW_PART_TAB_BTN,
        INDIC = LV_TABVIEW_PART_INDIC,
    };

    class Tabview final : public Object<Tabview> {
    public:

        Tabview() : Object(lv_tabview_create(lv_scr_act(), nullptr)) {}

        Page add_tab(const char *name) {
            return Page(lv_tabview_add_tab(get(), name));
        }

        void clean_tab() {
            return lv_tabview_clean_tab(get());
        }

        /*
         * SETTERS
         */

        Tabview &tab_act(uint16_t id, lv_anim_enable_t anim) {
            lv_tabview_set_tab_act(get(), id, anim);
            return this->underlying();
        }

        Tabview &anim_time(uint16_t anim_time) {
            lv_tabview_set_anim_time(get(), anim_time);
            return this->underlying();
        }

        Tabview &btns_pos(TabviewButtonsPosition btns_pos) {
            lv_tabview_set_btns_pos(get(), static_cast<lv_tabview_btns_pos_t>(btns_pos));
            return this->underlying();
        }

        /*
         * GETTERS
         */

        [[nodiscard]] uint16_t tab_act() const {
            return lv_tabview_get_tab_act(get());
        }

        [[nodiscard]] uint16_t tab_count() const {
            return lv_tabview_get_tab_count(get());
        }

        [[nodiscard]] Page tab(uint16_t id) const {
            return Page(lv_tabview_get_tab(get(), id));
        }

        [[nodiscard]] uint16_t anim_time() const {
            return lv_tabview_get_anim_time(get());
        }

        [[nodiscard]] lv_tabview_btns_pos_t btns_pos() const {
            return lv_tabview_get_btns_pos(get());
        }

    };
}

#endif // LV_USE_TABVIEW