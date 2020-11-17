#pragma once

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

    enum class ObjectPart {
        MAIN = LV_OBJ_PART_MAIN,
        ALL = LV_OBJ_PART_ALL
    };

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

    template<typename Derived = void>
    class Object : public detail::crtp<Derived, Object> {
    protected:
        friend class Page;

        explicit Object(lv_obj_t *other) noexcept: obj_(other) {};

    public:
        Object() noexcept: obj_(lv_obj_create(lv_scr_act(), nullptr)) {};

        template<typename T>
        explicit Object(const Object<T> &parent) noexcept
                : obj_(lv_obj_create(parent.raw(), nullptr)) {}

        template<typename T>
        explicit Object(const Object<T> &parent, const Object &copy) noexcept
                : obj_(lv_obj_create(parent.raw(), copy.raw())) {}

        explicit operator lv_obj_t *() { return obj_; }

        bool valid() { return obj_ != nullptr; };

        [[nodiscard]] lv_obj_t *raw() const {
            return obj_;
        }

        template<typename T>
        auto &parent(Object<T> &parent) {
            lv_obj_set_parent(raw(), parent.raw());
            return this->underlying();
        }

        auto &move_foreground() {
            lv_obj_move_foreground(raw());
            return this->underlying();
        }

        auto &move_background() {
            lv_obj_move_background(raw());
            return this->underlying();
        }

        auto &pos(lv_coord_t x, lv_coord_t y) {
            lv_obj_set_pos(raw(), x, y);
            return this->underlying();
        }

        auto &x(lv_coord_t x) {
            lv_obj_set_x(raw(), x);
            return this->underlying();
        }

        auto &y(lv_coord_t y) {
            lv_obj_set_y(raw(), y);
            return this->underlying();
        }

        auto &size(lv_coord_t w, lv_coord_t h) {
            lv_obj_set_size(raw(), w, h);
            return this->underlying();
        }

        auto &width(lv_coord_t w) {
            lv_obj_set_width(raw(), w);
            return this->underlying();
        }

        auto &height(lv_coord_t h) {
            lv_obj_set_height(raw(), h);
            return this->underlying();
        }

        auto &width_fit(lv_coord_t w) {
            lv_obj_set_width_fit(raw(), w);
            return this->underlying();
        }

        auto &height_fit(lv_coord_t h) {
            lv_obj_set_height_fit(raw(), h);
            return this->underlying();
        }

        auto &width_margin(lv_coord_t w) {
            lv_obj_set_width_margin(raw(), w);
            return this->underlying();
        }

        auto &height_margin(lv_coord_t h) {
            lv_obj_set_height_margin(raw(), h);
            return this->underlying();
        }

        auto &align(ObjectAlign align, lv_obj_t *base = nullptr, lv_coord_t x_shift = 0, lv_coord_t y_shift = 0) {
            lv_obj_align(raw(), base, static_cast<lv_align_t>(align), x_shift, y_shift);
            return this->underlying();
        }

        auto &align_mid(ObjectAlign align, lv_obj_t *base = nullptr, lv_coord_t x_shift = 0, lv_coord_t y_shift = 0) {
            lv_obj_align_mid(raw(), base, static_cast<lv_align_t>(align), x_shift, y_shift);
            return this->underlying();
        }

        auto &align_mid_x(ObjectAlign align, lv_obj_t *base = nullptr, lv_coord_t x_shift = 0) {
            lv_obj_align_mid_x(raw(), base, static_cast<lv_align_t>(align), x_shift);
            return this->underlying();
        }

        auto &align_mid_y(ObjectAlign align, lv_obj_t *base = nullptr, lv_coord_t y_shift = 0) {
            lv_obj_align_mid_y(raw(), base, static_cast<lv_align_t>(align), y_shift);
            return this->underlying();
        }

        auto &realign() {
            lv_obj_realign(raw());
            return this->underlying();
        }

        auto &auto_realign(bool enabled) {
            lv_obj_set_auto_realign(raw(), enabled);
            return this->underlying();
        }

        auto &ext_click_area(lv_area_t area) {
            lv_obj_set_ext_click_area(raw(), area.x1, area.x2, area.y1, area.y2);
            return this->underlying();
        }

        auto &add_style(Style &style, uint8_t part = LV_OBJ_PART_MAIN) {
            lv_obj_add_style(raw(), part, style);
            return this->underlying();
        }

        auto &remove_style(Style &style, uint8_t part = LV_OBJ_PART_MAIN) {
            lv_obj_remove_style(raw(), part, style);
            return this->underlying();
        }

        auto &clean_style_list(uint8_t part = LV_OBJ_PART_MAIN) {
            lv_obj_clean_style_list(raw(), part);
            return this->underlying();
        }

        auto &reset_style_list(uint8_t part = LV_OBJ_PART_MAIN) {
            lv_obj_reset_style_list(raw(), part);
            return this->underlying();
        }

        template<typename StyleProperty>
        auto &refresh_style() {
            lv_obj_refresh_style(raw(), StyleProperty::enum_value());
            return this->underlying();
        }

        auto &hidden(bool enabled) {
            lv_obj_set_hidden(raw(), enabled);
            return this->underlying();
        }

        auto &adv_hittest(bool enabled) {
            lv_obj_set_adv_hittest(raw(), enabled);
            return this->underlying();
        }

        auto &click(bool enabled) {
            lv_obj_set_click(raw(), enabled);
            return this->underlying();
        }

        auto &top(bool enabled) {
            lv_obj_set_top(raw(), enabled);
            return this->underlying();
        }

        auto &drag(bool enabled) {
            lv_obj_set_drag(raw(), enabled);
            return this->underlying();
        }

        auto &drag_dir(lv_drag_dir_t direction) {
            lv_obj_set_drag_dir(raw(), direction);
            return this->underlying();
        }

        auto &drag_throw(bool enabled) {
            lv_obj_set_drag_throw(raw(), enabled);
            return this->underlying();
        }

        auto &drag_parent(bool enabled) {
            lv_obj_set_drag_parent(raw(), enabled);
            return this->underlying();
        }

        auto &focus_parent(bool enabled) {
            lv_obj_set_focus_parent(raw(), enabled);
            return this->underlying();
        }

        auto &gesture_parent(bool enabled) {
            lv_obj_set_gesture_parent(raw(), enabled);
            return this->underlying();
        }

        auto &parent_event(bool enabled) {
            lv_obj_set_parent_event(raw(), enabled);
            return this->underlying();
        }

        auto &base_dir(lv_bidi_dir_t dir) {
            lv_obj_set_base_dir(raw(), dir);
            return this->underlying();
        }

        auto &add_protect(lv_protect_t prot) {
            lv_obj_add_protect(raw(), prot);
            return this->underlying();
        }

        auto &clear_protect(lv_protect_t prot) {
            lv_obj_clear_protect(raw(), prot);
            return this->underlying();
        }

        auto &state(ObjectState state) {
            lv_obj_set_state(raw(), static_cast<lv_state_t>(state));
            return this->underlying();
        }

        auto &add_state(ObjectState state) {
            lv_obj_add_state(raw(), static_cast<lv_state_t>(state));
            return this->underlying();
        }

        auto &clear_state(ObjectState state) {
            lv_obj_clear_state(raw(), static_cast<lv_state_t>(state));
            return this->underlying();
        }

#if LV_USE_ANIMATION

        auto &finish_transition(uint8_t part) {
            lv_obj_finish_transitions(raw(), part);
            return this->underlying();
        }

#endif

        auto &event_callback(lv_event_cb_t callback) {
            lv_obj_set_event_cb(raw(), callback);
            return this->underlying();
        }

        template<typename EventData>
        auto &send_event(lv_event_t event, const EventData *data) {
            lv_event_send(raw(), event, data);
            return this->underlying();
        }

        auto &signal_callback(lv_signal_cb_t callback) {
            lv_obj_set_signal_cb(raw(), callback);
            return this->underlying();
        }

        template<typename SignalData>
        auto &send_signal(lv_signal_t signal, const SignalData *data) {
            lv_signal_send(raw(), signal, data);
            return this->underlying();
        }

        auto &design_callback(lv_design_cb_t callback) {
            lv_obj_set_design_cb(raw(), callback);
            return this->underlying();
        }

        auto &allocate_ext_attr(uint16_t size) {
            lv_obj_allocate_ext_attr(raw(), size);
            return this->underlying();
        }

        auto &refresh_ext_draw_pad() {
            lv_obj_refresh_ext_draw_pad(raw());
            return this->underlying();
        }

        [[nodiscard]] auto screen() const {
            return Object(lv_obj_get_screen(raw()));
        }

        [[nodiscard]] auto display() const {
            return lv_obj_get_disp(raw());
        }

        [[nodiscard]] auto parent() const {
            return Object(lv_obj_get_parent(raw()));
        }

        [[nodiscard]] auto child() const {
            return Object(lv_obj_get_child(raw(), nullptr));
        }

        template<typename ObjectType>
        [[nodiscard]] auto child(const ObjectType &child) const {
            return Object(lv_obj_get_child(raw(), child.raw()));
        }

        [[nodiscard]] auto child_back() const {
            return Object(lv_obj_get_child_back(raw(), nullptr));
        }

        template<typename ObjectType>
        [[nodiscard]] auto child_back(const ObjectType &child) const {
            return Object(lv_obj_get_child_back(raw(), child.raw()));
        }

        [[nodiscard]] auto count_children() const {
            return lv_obj_count_children(raw());
        }

        [[nodiscard]] auto count_children_recursive() const {
            return lv_obj_count_children_recursive(raw());
        }

        ///

        [[nodiscard]] auto coords() const {
            lv_area_t area;
            lv_obj_get_coords(raw(), &area);
            return area;
        }

        [[nodiscard]] auto inner_coords() const {
            lv_area_t area;
            lv_obj_get_inner_coords(raw(), &area);
            return area;
        }

        [[nodiscard]] auto x() const {
            return lv_obj_get_x(raw());
        }

        [[nodiscard]] auto y() const {
            return lv_obj_get_y(raw());
        }

        [[nodiscard]] auto width() const {
            return lv_obj_get_width(raw());
        }

        [[nodiscard]] auto height() const {
            return lv_obj_get_height(raw());
        }

        [[nodiscard]] auto width_fit() const {
            return lv_obj_get_width_fit(raw());
        }

        [[nodiscard]] auto height_fit() const {
            return lv_obj_get_height_fit(raw());
        }

        [[nodiscard]] auto width_margin() const {
            return lv_obj_get_width_margin(raw());
        }

        [[nodiscard]] auto height_margin() const {
            return lv_obj_get_height_margin(raw());
        }

        [[nodiscard]] auto width_grid() const {
            return lv_obj_get_width_grid(raw());
        }

        [[nodiscard]] auto height_grid() const {
            return lv_obj_get_height_grid(raw());
        }

        [[nodiscard]] auto auto_realign() const {
            return lv_obj_get_auto_realign(raw());
        }

        [[nodiscard]] auto ext_click_pad_left() const {
            return lv_obj_get_ext_click_pad_left(raw());
        }

        [[nodiscard]] auto ext_click_pad_right() const {
            return lv_obj_get_ext_click_pad_right(raw());
        }

        [[nodiscard]] auto ext_click_pad_top() const {
            return lv_obj_get_ext_click_pad_top(raw());
        }

        [[nodiscard]] auto ext_click_pad_bottom() const {
            return lv_obj_get_ext_click_pad_bottom(raw());
        }

        [[nodiscard]] auto ext_draw_pad() const {
            return lv_obj_get_ext_draw_pad(raw());
        }

        template<typename PartType>
        [[nodiscard]] auto style_list(PartType part) const {
            return lv_obj_get_style_list(raw(), static_cast<uint8_t>(part));
        }

        template<typename PartType>
        auto local_style(PartType part) const {
            return lv_obj_get_local_style(raw(), static_cast<uint8_t>(part));
        }

        [[nodiscard]] auto hidden() const {
            return lv_obj_get_hidden(raw());
        }

        [[nodiscard]] auto adv_hittest() const {
            return lv_obj_get_adv_hittest(raw());
        }

        [[nodiscard]] auto click() const {
            return lv_obj_get_click(raw());
        }

        [[nodiscard]] auto top() const {
            return lv_obj_get_top(raw());
        }

        [[nodiscard]] auto drag() const {
            return lv_obj_get_drag(raw());
        }

        [[nodiscard]] auto drag_dir() const {
            return lv_obj_get_drag_dir(raw());
        }

        [[nodiscard]] auto get_throw() const {
            return lv_obj_get_throw(raw());
        }

        [[nodiscard]] auto drag_parent() const {
            return lv_obj_get_drag_parent(raw());
        }

        [[nodiscard]] auto focus_parent() const {
            return lv_obj_get_focus_parent(raw());
        }

        [[nodiscard]] bool get_parent_event() const {
            return lv_obj_get_parent_event(raw());
        }

        [[nodiscard]] bool get_gesture_parent() const {
            return lv_obj_get_gesture_parent(raw());
        }

        [[nodiscard]] lv_bidi_dir_t get_base_dir() const {
            return lv_obj_get_base_dir(raw());
        }

        [[nodiscard]] lv_protect_t get_protect() const {
            return lv_obj_get_protect(raw());
        }

        [[nodiscard]] bool is_protected(lv_protect_t protect) const {
            return lv_obj_is_protected(raw(), protect);
        }

        [[nodiscard]] lv_state_t get_state(ObjectPart part) const {
            return lv_obj_get_state(raw(), static_cast<lv_obj_part_t>(part));
        }

        [[nodiscard]] lv_signal_cb_t get_signal_cb() const {
            return lv_obj_get_signal_cb(raw());
        }

        [[nodiscard]] lv_design_cb_t get_design_cb() const {
            return lv_obj_get_design_cb(raw());
        }

        [[nodiscard]] lv_event_cb_t get_event_cb() const {
            return lv_obj_get_event_cb(raw());
        }

        [[nodiscard]] bool is_point_on_coords(const lv_point_t &point) const {
            return lv_obj_is_point_on_coords(raw(), &point);
        }

        [[nodiscard]] bool hittest(lv_point_t &point) const {
            return lv_obj_hittest(raw(), &point);
        }

        template<typename ExtAttr>
        [[nodiscard]] auto ext_attr() const {
            return static_cast<ExtAttr *>(lv_obj_get_ext_attr(raw()));
        }

        [[nodiscard]] lv_obj_type_t type() const {
            lv_obj_type_t type;
            lv_obj_get_type(raw(), &type);
            return type;
        }

#if LV_USE_USER_DATA

        [[nodiscard]] lv_obj_user_data_t get_user_data() const {
            return lv_obj_get_user_data(raw());
        }

        [[nodiscard]] lv_obj_user_data_t *get_user_data_ptr() const {
            return lv_obj_get_user_data_ptr(raw());
        }

        auto &user_data(const lv_obj_user_data_t &data) {
            lv_obj_set_user_data(raw(), data);
            return this->underlying();
        }

#endif

        [[nodiscard]] void *get_group() const {
            return lv_obj_get_group(raw());
        }

        [[nodiscard]] bool is_focussed() const {
            return lv_obj_is_focused(raw());
        }

        [[nodiscard]] auto focused_obj() const {
            return Object(lv_obj_get_focused_obj(raw()));
        }

        template<typename PartType>
        auto &init_draw_rect_dsc(PartType part, lv_draw_rect_dsc_t &dsc) {
            lv_obj_init_draw_rect_dsc(raw(), static_cast<uint8_t>(part), &dsc);
            return this->underlying();
        }

        template<typename PartType>
        auto &init_draw_label_dsc(PartType part, lv_draw_label_dsc_t &dsc) {
            lv_obj_init_draw_label_dsc(raw(), static_cast<uint8_t>(part), &dsc);
            return this->underlying();
        }

        template<typename PartType>
        auto &init_draw_img_dsc(PartType part, lv_draw_img_dsc_t &dsc) {
            lv_obj_init_draw_img_dsc(raw(), static_cast<uint8_t>(part), &dsc);
            return this->underlying();
        }

        template<typename PartType>
        auto &init_draw_line_dsc(PartType part, lv_draw_line_dsc_t &dsc) {
            lv_obj_init_draw_line_dsc(raw(), static_cast<uint8_t>(part), &dsc);
            return this->underlying();
        }

        template<typename PartType>
        [[nodiscard]] lv_coord_t get_draw_rect_ext_pad_size(PartType part) const {
            return lv_obj_get_draw_rect_ext_pad_size(raw(), static_cast<uint8_t>(part));
        }

        auto &fade_in(uint32_t time_ms, uint32_t delay_ms) {
            lv_obj_fade_in(raw(), time_ms, delay_ms);
            return this->underlying();
        }

        auto &fade_out(uint32_t time_ms, uint32_t delay_ms) {
            lv_obj_fade_out(raw(), time_ms, delay_ms);
            return this->underlying();
        }


        [[nodiscard]] bool debug_check_obj_type(const char *obj_type) const {
            return lv_debug_check_obj_type(raw(), obj_type);
        }

        [[nodiscard]] bool debug_check_obj_valid() const {
            return lv_debug_check_obj_valid(raw());
        }

        template<typename StyleProperty, ObjectState state = ObjectState::DEFAULT>
        auto &style(typename StyleProperty::value_type value, uint8_t part = LV_OBJ_PART_MAIN) {
            StyleProperty::set_value(raw(), value, part, static_cast<lv_state_t>(state));
            return this->underlying();
        }

        template<typename StyleProperty>
        typename StyleProperty::value_type style_value(uint8_t part = LV_OBJ_PART_MAIN) {
            return StyleProperty::get_value(raw(), part);
        }

    protected:
        lv_obj_t *obj_;

    };

}