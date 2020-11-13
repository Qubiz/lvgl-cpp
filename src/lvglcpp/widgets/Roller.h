#pragma once

#include "Object.h"

#if LV_USE_ROLLER

#include <span>

namespace lvglcpp {

    enum class RollerMode : lv_roller_mode_t {
        NORMAL = LV_ROLLER_MODE_NORMAL,
        INIFINITE = LV_ROLLER_MODE_INIFINITE,
    };

    enum class RollerPart : lv_roller_part_t {
        BG = LV_ROLLER_PART_BG,
        SELECTED = LV_ROLLER_PART_SELECTED,
    };

    class Roller : public Object<Roller> {
    protected:
        explicit Roller(lv_obj_t *other) noexcept: Object(other) {};

    public:

        Roller() noexcept: Object(lv_roller_create(lv_scr_act(), nullptr)) {};

        template<typename T>
        explicit Roller(const Object <T> &parent) noexcept
                : Object(lv_roller_create(parent.raw(), nullptr)) {}

        template<typename T>
        explicit Roller(const Object <T> &parent, const Roller &copy) noexcept
                : Object(lv_roller_create(parent.raw(), copy.raw())) {}

        /*
         * SETTERS
         */

        Roller &set_options(const char *options, RollerMode mode) {
            lv_roller_set_options(raw(), options, static_cast<lv_roller_mode_t>(mode));
            return this->underlying();
        }

        Roller &set_align(lv_label_align_t align) {
            lv_roller_set_align(raw(), align);
            return this->underlying();
        }

        Roller &set_selected(uint16_t sel_opt, lv_anim_enable_t anim) {
            lv_roller_set_selected(raw(), sel_opt, anim);
            return this->underlying();
        }

        Roller &set_visible_row_count(uint8_t row_cnt) {
            lv_roller_set_visible_row_count(raw(), row_cnt);
            return this->underlying();
        }

        Roller &set_auto_fit(bool auto_fit) {
            lv_roller_set_auto_fit(raw(), auto_fit);
            return this->underlying();
        }

        Roller &set_anim_time(uint16_t anim_time) {
            lv_roller_set_anim_time(raw(), anim_time);
            return this->underlying();
        }

        /*
         * GETTERS
         */

        [[nodiscard]] uint16_t selected() const {
            return lv_roller_get_selected(raw());
        }

        [[nodiscard]] uint16_t option_cnt() const {
            return lv_roller_get_option_cnt(raw());
        }

        void selected_str(std::span<char *> buf) const {
            return lv_roller_get_selected_str(raw(), reinterpret_cast<char *>(buf.data()), buf.size());
        }

        [[nodiscard]] lv_label_align_t align() const {
            return lv_roller_get_align(raw());
        }

        [[nodiscard]] bool auto_fit(lv_obj_t *roller) const {
            return lv_roller_get_auto_fit(raw());
        }

        [[nodiscard]] const char *options() const {
            return lv_roller_get_options(raw());
        }

        [[nodiscard]] uint16_t anim_time() const {
            return lv_roller_get_anim_time(raw());
        }

    };
}

#endif // LV_USE_ROLLER
