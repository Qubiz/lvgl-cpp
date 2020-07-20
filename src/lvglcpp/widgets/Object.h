#pragma once

#ifndef LVGL_CPP_OBJECT_H
#define LVGL_CPP_OBJECT_H

#include <type_traits>

#include "../core/Style.h"

namespace lvglcpp {

    namespace detail {
        template<typename T, template<typename> typename crtpType>
        struct crtp {
            auto &underlying() {
                if constexpr (std::is_same_v<T, void>) {
                    return static_cast<crtpType<T> &>(*this);
                } else {
                    return static_cast<T &>(*this);
                }

            }

            auto &underlying() const {
                if constexpr (std::is_same_v<T, void>) {
                    return static_cast<crtpType<T> &>(*this);
                } else {
                    return static_cast<T &>(*this);
                }
            }

        private:
            friend crtpType<T>;
            friend T;
        };
    }

    template<typename Derived>
    class Object;

    enum class ObjectAlign : lv_align_t {
        CENTER = LV_ALIGN_CENTER,
        IN_TOP_LEFT = LV_ALIGN_IN_TOP_LEFT,
        IN_TOP_MID = LV_ALIGN_IN_TOP_MID,
        IN_TOP_RIGHT = LV_ALIGN_IN_TOP_RIGHT,
        IN_BOTTOM_LEFT = LV_ALIGN_IN_BOTTOM_LEFT,
        IN_BOTTOM_MID = LV_ALIGN_IN_BOTTOM_MID,
        IN_BOTTOM_RIGHT = LV_ALIGN_IN_BOTTOM_RIGHT,
        IN_LEFT_MID = LV_ALIGN_IN_LEFT_MID,
        IN_RIGHT_MID = LV_ALIGN_IN_RIGHT_MID,
        OUT_TOP_LEFT = LV_ALIGN_OUT_TOP_LEFT,
        OUT_TOP_MID = LV_ALIGN_OUT_TOP_MID,
        OUT_TOP_RIGHT = LV_ALIGN_OUT_TOP_RIGHT,
        OUT_BOTTOM_LEFT = LV_ALIGN_OUT_BOTTOM_LEFT,
        OUT_BOTTOM_MID = LV_ALIGN_OUT_BOTTOM_MID,
        OUT_BOTTOM_RIGHT = LV_ALIGN_OUT_BOTTOM_RIGHT,
        OUT_LEFT_TOP = LV_ALIGN_OUT_LEFT_TOP,
        OUT_LEFT_MID = LV_ALIGN_OUT_LEFT_MID,
        OUT_LEFT_BOTTOM = LV_ALIGN_OUT_LEFT_BOTTOM,
        OUT_RIGHT_TOP = LV_ALIGN_OUT_RIGHT_TOP,
        OUT_RIGHT_MID = LV_ALIGN_OUT_RIGHT_MID,
        OUT_RIGHT_BOTTOM = LV_ALIGN_OUT_RIGHT_BOTTOM,
    };

    enum class ObjectPart : lv_obj_part_t {
        MAIN = LV_OBJ_PART_MAIN,
        ALL = LV_OBJ_PART_ALL
    };

    enum class ObjectState : lv_state_t {
        DEFAULT = LV_STATE_DEFAULT,
        CHECKED = LV_STATE_CHECKED,
        FOCUSED = LV_STATE_FOCUSED,
        EDITED = LV_STATE_EDITED,
        HOVERED = LV_STATE_HOVERED,
        PRESSED = LV_STATE_PRESSED,
        DISABLED = LV_STATE_DISABLED,
    };

    template<typename Derived = void>
    class Object : public detail::crtp<Derived, Object> {
    public:
        /**
         * Construct a new object and take ownership. The object will be created on the
         * current active screen.
         */
        explicit Object() noexcept: obj_(lv_obj_create(lv_scr_act(), nullptr)) {}

        /**
         * Copy constructor. Creates a copy of the given object with
         * the currently active screen as its parent.
         * @param copy The object to copy.
         */
        Object(const Object &copy) noexcept: obj_(lv_obj_create(lv_scr_act(), copy.get())) {}

        /**
         * Copy constructor. Creates a copy of an object with the given parent.
         * @param parent The parent of the object.
         * @param copy The object to copy.
         */
        Object(const Object &parent, const Object &copy) noexcept: obj_(lv_obj_create(parent.get(), copy.get())) {}

        operator lv_obj_t *() { return get(); }

        /**
         * Returns a pointer to the underlying raw LVGL object.
         * @return The raw LVGL object pointer.
         */
        [[nodiscard]] lv_obj_t *get() const {
            return obj_;
        }

        template<typename T>
        auto &parent(Object<T> &parent) {
            lv_obj_set_parent(get(), parent.get());
            return this->underlying();
        }

        auto &moveForeground() {
            lv_obj_move_foreground(get());
            return this->underlying();
        }

        auto &moveBackground() {
            lv_obj_move_background(get());
            return this->underlying();
        }

        auto &pos(lv_coord_t x, lv_coord_t y) {
            lv_obj_set_pos(get(), x, y);
            return this->underlying();
        }

        auto &x(lv_coord_t x) {
            lv_obj_set_x(get(), x);
            return this->underlying();
        }

        auto &y(lv_coord_t y) {
            lv_obj_set_y(get(), y);
            return this->underlying();
        }

        auto &size(lv_coord_t w, lv_coord_t h) {
            lv_obj_set_size(get(), w, h);
            return this->underlying();
        }

        auto &width(lv_coord_t w) {
            lv_obj_set_width(get(), w);
            return this->underlying();
        }

        auto &height(lv_coord_t h) {
            lv_obj_set_height(get(), h);
            return this->underlying();
        }

        auto &width_fit(lv_coord_t w) {
            lv_obj_set_width_fit(get(), w);
            return this->underlying();
        }

        auto &height_fit(lv_coord_t h) {
            lv_obj_set_height_fit(get(), h);
            return this->underlying();
        }

        auto &width_margin(lv_coord_t w) {
            lv_obj_set_width_margin(get(), w);
            return this->underlying();
        }

        auto &height_margin(lv_coord_t h) {
            lv_obj_set_height_margin(get(), h);
            return this->underlying();
        }

        auto &align(ObjectAlign align, lv_obj_t *base = nullptr, lv_coord_t x_shift = 0, lv_coord_t y_shift = 0) {
            lv_obj_align(get(), base, static_cast<lv_align_t>(align), x_shift, y_shift);
            return this->underlying();
        }

        auto &align_origo(ObjectAlign align, lv_obj_t *base = nullptr, lv_coord_t x_shift = 0, lv_coord_t y_shift = 0) {
            lv_obj_align_origo(get(), base, static_cast<lv_align_t>(align), x_shift, y_shift);
            return this->underlying();
        }

        auto &realign() {
            lv_obj_realign(get());
            return this->underlying();
        }

        auto &auto_realign(bool enabled) {
            lv_obj_set_auto_realign(get(), enabled);
            return this->underlying();
        }

        auto &ext_click_area(lv_area_t area) {
            lv_obj_set_ext_click_area(get(), area.x1, area.x2, area.y1, area.y2);
            return this->underlying();
        }

        auto &add_style(lv_style_t *style, uint8_t part = LV_OBJ_PART_MAIN) {
            lv_obj_add_style(get(), part, style);
            return this->underlying();
        }

        auto &remove_style(lv_style_t *style, uint8_t part = LV_OBJ_PART_MAIN) {
            lv_obj_remove_style(get(), part, style);
            return this->underlying();
        }

        auto &clean_style_list(uint8_t part = LV_OBJ_PART_MAIN) const {
            lv_obj_clean_style_list(get(), part);
            return this->underlying();
        }

        auto &reset_style_list(uint8_t part = LV_OBJ_PART_MAIN) const {
            lv_obj_reset_style_list(get(), part);
            return this->underlying();
        }

        template<typename StyleProperty>
        auto &refresh_style() {
            lv_obj_refresh_style(get(), StyleProperty::enum_value());
            return this->underlying();
        }

        auto &hidden(bool enabled) {
            lv_obj_set_hidden(get(), enabled);
            return this->underlying();
        }

        auto &adv_hittest(bool enabled) {
            lv_obj_set_adv_hittest(get(), enabled);
            return this->underlying();
        }

        auto &click(bool enabled) {
            lv_obj_set_click(get(), enabled);
            return this->underlying();
        }

        auto &top(bool enabled) {
            lv_obj_set_top(get(), enabled);
            return this->underlying();
        }

        auto &drag(bool enabled) {
            lv_obj_set_drag(get(), enabled);
            return this->underlying();
        }

        auto &drag_dir(lv_drag_dir_t direction) {
            lv_obj_set_drag_dir(get(), direction);
            return this->underlying();
        }

        auto &drag_throw(bool enabled) {
            lv_obj_set_drag_throw(get(), enabled);
            return this->underlying();
        }

        auto &drag_parent(bool enabled) {
            lv_obj_set_drag_parent(get(), enabled);
            return this->underlying();
        }

        auto &focus_parent(bool enabled) {
            lv_obj_set_focus_parent(get(), enabled);
            return this->underlying();
        }

        auto &gesture_parent(bool enabled) {
            lv_obj_set_gesture_parent(get(), enabled);
            return this->underlying();
        }

        auto &parent_event(bool enabled) {
            lv_obj_set_parent_event(get(), enabled);
            return this->underlying();
        }

        auto &base_dir(lv_bidi_dir_t dir) {
            lv_obj_set_base_dir(get(), dir);
            return this->underlying();
        }

        auto &add_protect(lv_protect_t prot) {
            lv_obj_add_protect(get(), prot);
            return this->underlying();
        }

        auto &clear_protect(lv_protect_t prot) {
            lv_obj_clear_protect(get(), prot);
            return this->underlying();
        }

        auto &state(lv_state_t state) {
            lv_obj_set_state(get(), state);
            return this->underlying();
        }

        auto &addState(lv_state_t state) {
            lv_obj_add_state(get(), state);
            return this->underlying();
        }

        auto &clearState(lv_state_t state) {
            lv_obj_clear_state(get(), state);
            return this->underlying();
        }

#if LV_USE_ANIMATION

        auto &finish_transition(uint8_t part) const {
            lv_obj_finish_transitions(get(), part);
            return this->underlying();
        }

#endif

        auto &event_callback(lv_event_cb_t callback) {
            lv_obj_set_event_cb(get(), callback);
            return this->underlying();
        }

        template<typename EventData>
        auto &send_event(lv_event_t event, const EventData *data) {
            lv_event_send(get(), event, data);
            return this->underlying();
        }

        auto &signal_callback(lv_signal_cb_t callback) {
            lv_obj_set_signal_cb(get(), callback);
            return this->underlying();
        }

        template<typename SignalData>
        auto &send_signal(lv_signal_t signal, const SignalData *data) {
            lv_signal_send(get(), signal, data);
            return this->underlying();
        }

        auto &style_pad_all(lv_style_int_t value, uint8_t part = LV_OBJ_PART_MAIN,
                            ObjectState state = ObjectState::DEFAULT) {
            lv_obj_set_style_local_pad_all(get(), part, state, value);
            return this->underlying();
        }

        auto &style_pad_hor(lv_style_int_t value, uint8_t part = LV_OBJ_PART_MAIN,
                            ObjectState state = ObjectState::DEFAULT) {
            lv_obj_set_style_local_pad_hor(get(), part, state, value);
            return this->underlying();
        }

        auto &style_pad_ver(lv_style_int_t value, uint8_t part = LV_OBJ_PART_MAIN,
                            ObjectState state = ObjectState::DEFAULT) {
            lv_obj_set_style_local_pad_ver(get(), part, state, value);
            return this->underlying();
        }

        auto &style_margin_all(lv_style_int_t value, uint8_t part = LV_OBJ_PART_MAIN,
                               ObjectState state = ObjectState::DEFAULT) {
            lv_obj_set_style_local_margin_all(get(), part, state, value);
            return this->underlying();
        }

        auto &style_margin_hor(lv_style_int_t value, uint8_t part = LV_OBJ_PART_MAIN,
                               ObjectState state = ObjectState::DEFAULT) {
            lv_obj_set_style_local_margin_hor(get(), part, state, value);
            return this->underlying();
        }

        auto &style_margin_ver(lv_style_int_t value, uint8_t part = LV_OBJ_PART_MAIN,
                               ObjectState state = ObjectState::DEFAULT) {
            lv_obj_set_style_local_margin_ver(get(), part, state, value);
            return this->underlying();
        }

        auto &design_callback(lv_design_cb_t callback) {
            lv_obj_set_design_cb(get(), callback);
            return this->underlying();
        }

        auto &allocate_ext_attr(uint16_t size) {
            lv_obj_allocate_ext_attr(get(), size);
            return this->underlying();
        }

        auto &refresh_ext_draw_pad() {
            lv_obj_refresh_ext_draw_pad(get());
            return this->underlying();
        }

        [[nodiscard]] auto screen() const {
            return Object(lv_obj_get_screen(get()));
        }

        [[nodiscard]] auto display() const {
            return lv_obj_get_disp(get());
        }

        [[nodiscard]] auto parent() const {
            return Object(lv_obj_get_parent(get()));
        }

        template<typename T>
        [[nodiscard]] auto child(const Object<T> *child = nullptr) const {
            return Object(lv_obj_get_child(get(), child->get()));
        }

        template<typename T>
        [[nodiscard]] auto child_back(const Object<T> *child = nullptr) const {
            return Object(lv_obj_get_parent(get(), child->get()));
        }

        auto count_children() const {
            return lv_obj_count_children(get());
        }

        auto count_children_recursive() const {
            return lv_obj_count_children_recursive(get());
        }

        ///

        auto coords() const {
            lv_area_t area;
            lv_obj_get_coords(get(), &area);
            return area;
        }

        auto inner_coords() const {
            lv_area_t area;
            lv_obj_get_inner_coords(get(), &area);
            return area;
        }

        auto x() const {
            return lv_obj_get_x(get());
        }

        auto y() const {
            return lv_obj_get_y(get());
        }

        auto width() const {
            return lv_obj_get_width(get());
        }

        auto height() const {
            return lv_obj_get_height(get());
        }

        auto width_fit() const {
            return lv_obj_get_width_fit(get());
        }

        auto height_fit() const {
            return lv_obj_get_height_fit(get());
        }

        auto width_margin() const {
            return lv_obj_get_width_margin(get());
        }

        auto height_margin() const {
            return lv_obj_get_height_margin(get());
        }

        auto width_grid() const {
            return lv_obj_get_width_grid(get());
        }

        auto height_grid() const {
            return lv_obj_get_height_grid(get());
        }

        auto auto_realign() const {
            return lv_obj_get_auto_realign(get());
        }

        auto ext_click_pad_left() const {
            return lv_obj_get_ext_click_pad_left(get());
        }

        auto ext_click_pad_right() const {
            return lv_obj_get_ext_click_pad_right(get());
        }

        auto ext_click_pad_top() const {
            return lv_obj_get_ext_click_pad_top(get());
        }

        auto ext_click_pad_bottom() const {
            return lv_obj_get_ext_click_pad_bottom(get());
        }

        auto ext_draw_pad() const {
            return lv_obj_get_ext_draw_pad(get());
        }

        [[nodiscard]] auto style_list(ObjectPart part) const {
            return lv_obj_get_style_list(get(), part);
        }

        auto local_style(ObjectPart part) const {
            return lv_obj_get_local_style(get(), part);
        }

        auto hidden() const {
            return lv_obj_get_hidden(get());
        }

        auto adv_hittest() const {
            return lv_obj_get_adv_hittest(get());
        }

        auto click() const {
            return lv_obj_get_click(get());
        }

        auto top() const {
            return lv_obj_get_top(get());
        }

        auto drag() const {
            return lv_obj_get_drag(get());
        }

        auto drag_dir() const {
            return lv_obj_get_drag_dir(get());
        }

        auto get_throw() const {
            return lv_obj_get_throw(get());
        }

        auto drag_parent() const {
            return lv_obj_get_drag_parent(get());
        }

        auto focus_parent() const {
            return lv_obj_get_focus_parent(get());
        }

        [[nodiscard]] bool get_parent_event() const {
            return lv_obj_get_parent_event(get());
        }

        [[nodiscard]] bool get_gesture_parent() const {
            return lv_obj_get_gesture_parent(get());
        }

        [[nodiscard]] lv_bidi_dir_t get_base_dir() const {
            return lv_obj_get_base_dir(get());
        }

        [[nodiscard]] lv_protect_t get_protect() const {
            return lv_obj_get_protect(get());
        }

        [[nodiscard]] bool is_protected(lv_protect_t protect) const {
            return lv_obj_is_protected(get(), protect);
        }

        [[nodiscard]] lv_state_t get_state(ObjectPart part) const {
            return lv_obj_get_state(get(), part);
        }

        [[nodiscard]] lv_signal_cb_t get_signal_cb() const {
            return lv_obj_get_signal_cb(get());
        }

        [[nodiscard]] lv_design_cb_t get_design_cb() const {
            return lv_obj_get_design_cb(get());
        }

        [[nodiscard]] lv_event_cb_t get_event_cb() const {
            return lv_obj_get_event_cb(get());
        }

        [[nodiscard]] bool is_point_on_coords(const lv_point_t &point) const {
            return lv_obj_is_point_on_coords(get(), &point);
        }

        [[nodiscard]] bool hittest(lv_point_t &point) const {
            return lv_obj_hittest(get(), &point);
        }

        template<typename ExtAttr>
        [[nodiscard]] auto ext_attr() const {
            return static_cast<ExtAttr *>(lv_obj_get_ext_attr(get()));
        }

        [[nodiscard]] lv_obj_type_t get_type() const {
            lv_obj_type_t type;
            lv_obj_get_type(get(), &type);
            return type;
        }

#if LV_USE_USER_DATA

        [[nodiscard]] lv_obj_user_data_t get_user_data() const {
            return lv_obj_get_user_data(get());
        }

        [[nodiscard]] lv_obj_user_data_t *get_user_data_ptr() const {
            return lv_obj_get_user_data_ptr(get());
        }

        auto &user_data(const lv_obj_user_data_t &data) {
            lv_obj_set_user_data(get(), data);
            return this->underlying();
        }

#endif

        [[nodiscard]] void *get_group() const {
            return lv_obj_get_group(get());
        }

        [[nodiscard]] bool is_focussed() const {
            return lv_obj_is_focused(get());
        }

        auto focused_obj() const {
            return Object(lv_obj_get_focused_obj(get()));
        }

        auto &init_draw_rect_dsc(ObjectPart part, lv_draw_rect_dsc_t &dsc) {
            lv_obj_init_draw_rect_dsc(get(), part, &dsc);
            return this->underlying();
        }

        auto &init_draw_label_dsc(ObjectPart part, lv_draw_label_dsc_t &dsc) {
            lv_obj_init_draw_label_dsc(get(), part, &dsc);
            return this->underlying();
        }

        auto &init_draw_img_dsc(ObjectPart part, lv_draw_img_dsc_t &dsc) {
            lv_obj_init_draw_img_dsc(get(), part, &dsc);
            return this->underlying();
        }

        auto &init_draw_line_dsc(ObjectPart part, lv_draw_line_dsc_t &dsc) {
            lv_obj_init_draw_line_dsc(get(), part, &dsc);
            return this->underlying();
        }

        [[nodiscard]] lv_coord_t get_draw_rect_ext_pad_size(ObjectPart part) const {
            return lv_obj_get_draw_rect_ext_pad_size(get(), part);
        }

        auto &fade_in(uint32_t time_ms, uint32_t delay_ms) {
            lv_obj_fade_in(get(), time_ms, delay_ms);
            return this->underlying();
        }

        auto &fade_out(uint32_t time_ms, uint32_t delay_ms) {
            lv_obj_fade_out(get(), time_ms, delay_ms);
            return this->underlying();
        }


        [[nodiscard]] bool debug_check_obj_type(const char *obj_type) const {
            return lv_debug_check_obj_type(get(), obj_type);
        }

        [[nodiscard]] bool debug_check_obj_valid() const {

            return lv_debug_check_obj_valid(get());
        }

        template<typename StyleProperty>
        auto &style(typename StyleProperty::value_type value, uint8_t part = LV_OBJ_PART_MAIN,
                    ObjectState state = ObjectState::DEFAULT) {
            StyleProperty::set_value(get(), value, part, static_cast<lv_state_t>(state));
            return this->underlying();
        }

        template<typename StyleProperty>
        typename StyleProperty::value_type style_value(uint8_t part = LV_OBJ_PART_MAIN) {
            return StyleProperty::get_value(get(), part);
        }

    protected:
        /**
         * Construct an object by taking ownership of an existing LVGL object pointer.
         * @param other The raw LVGL object pointer to take ownership of.
         */
        explicit Object(lv_obj_t *other) noexcept: obj_(other) {}

    private:
        lv_obj_t *obj_;

    };

}

#endif //LVGL_CPP_OBJECT_H