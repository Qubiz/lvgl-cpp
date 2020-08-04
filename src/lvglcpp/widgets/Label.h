#pragma once

#include "Object.h"

#if LV_USE_LABEL

namespace lvglcpp {

    enum class LabelPart : lv_obj_part_t {
        MAIN = LV_LABEL_PART_MAIN,
    };

    enum class LabelLongMode : lv_label_long_mode_t {
        LONG_EXPAND = LV_LABEL_LONG_EXPAND,
        LONG_BREAK = LV_LABEL_LONG_BREAK,
        LONG_DOT = LV_LABEL_LONG_DOT,
        LONG_SROLL = LV_LABEL_LONG_SROLL,
        LONG_SROLL_CIRC = LV_LABEL_LONG_SROLL_CIRC,
        LONG_CROP = LV_LABEL_LONG_CROP,
    };

    enum class LabelAlign : lv_label_align_t {
        AUTO = LV_LABEL_ALIGN_AUTO,
        LEFT = LV_LABEL_ALIGN_LEFT,
        RIGHT = LV_LABEL_ALIGN_RIGHT,
        CENTER = LV_LABEL_ALIGN_CENTER
    };

    class Label final : public Object<Label> {
    protected:
        explicit Label(lv_obj_t *other) noexcept: Object(other) {};

        friend class List;

    public:

        Label() noexcept: Object(lv_label_create(lv_scr_act(), nullptr)) {};

        template<typename T>
        explicit Label(const Object <T> &parent) noexcept
                : Object(lv_label_create(parent.get(), nullptr)) {}

        template<typename T>
        explicit Label(const Object <T> &parent, const Label &copy) noexcept
                : Object(lv_label_create(parent.get(), copy.get())) {}

        explicit Label(const char *txt) : Label() {
            text(txt);
        }

        template<typename T>
        explicit Label(const char *txt, const Object <T> &parent) : Label(parent) {
            text(txt);
        }

        template<typename T>
        explicit Label(const char *txt, const Object <T> &parent, const Label &copy) : Label(parent, copy) {
            text(txt);
        }

        Label &text(const char *text) {
            lv_label_set_text(get(), text);
            return this->underlying();
        }

        template<typename ... Args>
        Label &text_fmt(const char *text, const Args &... args) {
            lv_label_set_text_fmt(get(), text, args...);
            return this->underlying();
        }

        Label &text_static(const char *text) {
            lv_label_set_text_static(get(), text);
            return this->underlying();
        }

        Label &long_mode(LabelLongMode mode) {
            lv_label_set_long_mode(get(), static_cast<lv_label_long_mode_t>(mode));
            return this->underlying();
        }

        using Object::align;

        Label &align(const LabelAlign align) {
            lv_label_set_align(get(), static_cast<lv_label_align_t>(align));
            return this->underlying();
        }

        Label &recolor(bool enabled) {
            lv_label_set_recolor(get(), enabled);
            return this->underlying();
        }

        Label &anim_speed(uint16_t speed) {
            lv_label_set_anim_speed(get(), speed);
            return this->underlying();
        }

        Label &text_sel_start(uint32_t index) {
            lv_label_set_text_sel_start(get(), index);
            return this->underlying();
        }

        Label &text_sel_end(uint32_t index) {
            lv_label_set_text_sel_end(get(), index);
            return this->underlying();
        }

        [[nodiscard]] char *text() const {
            return lv_label_get_text(get());
        }

        [[nodiscard]] LabelLongMode long_mode() const {
            return static_cast<LabelLongMode>(lv_label_get_long_mode(get()));
        }

        [[nodiscard]] LabelAlign align() const {
            return static_cast<LabelAlign>(lv_label_get_align(get()));
        }

        bool recolor() {
            return lv_label_get_recolor(get());
        }

        uint16_t anim_speed() {
            return lv_label_get_anim_speed(get());
        }

        lv_point_t letter_pos(uint32_t index) {
            lv_point_t point;
            lv_label_get_letter_pos(get(), index, &point);
            return point;
        }

        uint32_t letter_on(lv_point_t &point) {
            return lv_label_get_letter_on(get(), &point);
        }

        bool is_char_under_pos(lv_point_t &point) {
            return lv_label_is_char_under_pos(get(), &point);
        }

        uint32_t text_sel_start() {
            return lv_label_get_text_sel_start(get());
        }

        uint32_t text_sel_end() {
            return lv_label_get_text_sel_end(get());
        }

        auto &ins_text(uint32_t pos, const char *text) {
            lv_label_ins_text(get(), pos, text);
            return this->underlying();
        }

        auto &cut_text(uint32_t pos, uint32_t count) {
            lv_label_cut_text(get(), pos, count);
            return this->underlying();
        }
    };

}

#endif // LV_USE_LABEL
