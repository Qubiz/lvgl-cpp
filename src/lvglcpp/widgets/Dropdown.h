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

    class Dropdown final : public Object<Dropdown> {
    protected:
        explicit Dropdown(lv_obj_t *other) noexcept: Object(other) {};

    public:

        Dropdown() noexcept: Object(lv_dropdown_create(lv_scr_act(), nullptr)) {};
template<typename T>
        explicit Dropdown(const Object<T> &parent) noexcept
                : Object(lv_dropdown_create(parent.get(), nullptr)) {}
template<typename T>
        explicit Dropdown(const Object<T> &parent, const Dropdown &copy) noexcept
                : Object(lv_dropdown_create(parent.get(), copy.get())) {}

        /*
         * SETTERS
         */

        Dropdown &text(const char *txt) {
            lv_dropdown_set_text(get(), txt);
            return this->underlying();
        }

        Dropdown &r_options() {
            lv_dropdown_clear_options(get());
            return this->underlying();
        }

        Dropdown &options(const char *options) {
            lv_dropdown_set_options(get(), options);
            return this->underlying();
        }

        Dropdown &options_static(const char *options) {
            lv_dropdown_set_options_static(get(), options);
            return this->underlying();
        }

        Dropdown &option(const char *option, uint32_t pos) {
            lv_dropdown_add_option(get(), option, pos);
            return this->underlying();
        }

        Dropdown &selected(uint16_t sel_opt) {
            lv_dropdown_set_selected(get(), sel_opt);
            return this->underlying();
        }

        Dropdown &dir(DropdownDirection dir) {
            lv_dropdown_set_dir(get(), static_cast<lv_dropdown_dir_t>(dir));
            return this->underlying();
        }

        Dropdown &max_height(lv_coord_t h) {
            lv_dropdown_set_max_height(get(), h);
            return this->underlying();
        }

        Dropdown &symbol(const char *symbol) {
            lv_dropdown_set_symbol(get(), symbol);
            return this->underlying();
        }

        Dropdown &show_selected(bool show) {
            lv_dropdown_set_show_selected(get(), show);
            return this->underlying();
        }

        /*
         * GETTERS
         */

        [[nodiscard]] const char * text() const {
            return lv_dropdown_get_text(get());
        }
        [[nodiscard]] const char * options() const {
            return lv_dropdown_get_options(get());
        }
        [[nodiscard]] uint16_t selected() const {
            return  lv_dropdown_get_selected(get());
        }
        [[nodiscard]] uint16_t option_cnt() const {
            return  lv_dropdown_get_option_cnt(get());
        }
        void selected_str(std::span<char *> s) {
            return lv_dropdown_get_selected_str(get(), reinterpret_cast<char *>(s.data()), s.size());
        }
        [[nodiscard]] lv_coord_t max_height() const {
            return lv_dropdown_get_max_height(get());
        }
        [[nodiscard]] const char * symbol() const {
            return lv_dropdown_get_symbol(get());
        }
        [[nodiscard]] DropdownDirection dir() const {
            return static_cast<DropdownDirection>(lv_dropdown_get_dir(get()));
        }
        [[nodiscard]] bool show_selected() const {
            return lv_dropdown_get_show_selected(get());
        }

        /*
         * OTHER
         */
        Dropdown &open() {
            lv_dropdown_open(get());
            return this->underlying();
        }

        Dropdown &close() {
            lv_dropdown_close(get());
            return this->underlying();
        }

    };
}

#endif // LV_USE_DROPDOWN