#pragma once

#include "Object.h"

#if LV_USE_DROPDOWN

#include <string_view>

namespace lvglcpp {

    enum class DropdownDirection : lv_dropdown_dir_t {
        DOWN = LV_DROPDOWN_DIR_DOWN,
        UP = LV_DROPDOWN_DIR_UP,
        LEFT = LV_DROPDOWN_DIR_LEFT,
        RIGHT = LV_DROPDOWN_DIR_RIGHT,
    };

    enum class DropdownPart : lv_dropdown_part_t {
        MAIN = LV_DROPDOWN_PART_MAIN,
        LIST = LV_DROPDOWN_PART_LIST,
        SCROLLBAR = LV_DROPDOWN_PART_SCROLLBAR,
        SELECTED = LV_DROPDOWN_PART_SELECTED,
    };

    class Dropdown : public Object<Dropdown> {
    protected:
        explicit Dropdown(lv_obj_t *other) noexcept: Object(other) {};

    public:

        Dropdown() noexcept: Object(lv_dropdown_create(lv_scr_act(), nullptr)) {};

        template<typename T>
        explicit Dropdown(const Object <T> &parent) noexcept
                : Object(lv_dropdown_create(parent.raw(), nullptr)) {}

        template<typename T>
        explicit Dropdown(const Object <T> &parent, const Dropdown &copy) noexcept
                : Object(lv_dropdown_create(parent.raw(), copy.raw())) {}

        /*
         * SETTERS
         */

        Dropdown &text(const char *txt) {
            lv_dropdown_set_text(raw(), txt);
            return this->underlying();
        }

        Dropdown &r_options() {
            lv_dropdown_clear_options(raw());
            return this->underlying();
        }

        Dropdown &options(const char *options) {
            lv_dropdown_set_options(raw(), options);
            return this->underlying();
        }

        Dropdown &options_static(const char *options) {
            lv_dropdown_set_options_static(raw(), options);
            return this->underlying();
        }

        Dropdown &option(const char *option, uint32_t pos) {
            lv_dropdown_add_option(raw(), option, pos);
            return this->underlying();
        }

        Dropdown &selected(uint16_t sel_opt) {
            lv_dropdown_set_selected(raw(), sel_opt);
            return this->underlying();
        }

        Dropdown &dir(DropdownDirection dir) {
            lv_dropdown_set_dir(raw(), static_cast<lv_dropdown_dir_t>(dir));
            return this->underlying();
        }

        Dropdown &max_height(lv_coord_t h) {
            lv_dropdown_set_max_height(raw(), h);
            return this->underlying();
        }

        Dropdown &symbol(const char *symbol) {
            lv_dropdown_set_symbol(raw(), symbol);
            return this->underlying();
        }

        Dropdown &show_selected(bool show) {
            lv_dropdown_set_show_selected(raw(), show);
            return this->underlying();
        }

        /*
         * GETTERS
         */

        [[nodiscard]] const char *text() const {
            return lv_dropdown_get_text(raw());
        }

        [[nodiscard]] const char *options() const {
            return lv_dropdown_get_options(raw());
        }

        [[nodiscard]] uint16_t selected() const {
            return lv_dropdown_get_selected(raw());
        }

        [[nodiscard]] uint16_t option_cnt() const {
            return lv_dropdown_get_option_cnt(raw());
        }

        void selected_str(std::span<char *> s) {
            return lv_dropdown_get_selected_str(raw(), reinterpret_cast<char *>(s.data()), s.size());
        }

        [[nodiscard]] lv_coord_t max_height() const {
            return lv_dropdown_get_max_height(raw());
        }

        [[nodiscard]] const char *symbol() const {
            return lv_dropdown_get_symbol(raw());
        }

        [[nodiscard]] DropdownDirection dir() const {
            return static_cast<DropdownDirection>(lv_dropdown_get_dir(raw()));
        }

        [[nodiscard]] bool show_selected() const {
            return lv_dropdown_get_show_selected(raw());
        }

        /*
         * OTHER
         */
        Dropdown &open() {
            lv_dropdown_open(raw());
            return this->underlying();
        }

        Dropdown &close() {
            lv_dropdown_close(raw());
            return this->underlying();
        }

    };
}

#endif // LV_USE_DROPDOWN