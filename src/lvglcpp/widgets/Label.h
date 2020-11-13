#pragma once

#include "Object.h"

#include <utility>

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

    class Label : public Object<Label> {
    protected:
        explicit Label(lv_obj_t *other) noexcept: Object(other) {};

        friend class List;

    public:

        Label() noexcept: Object(lv_label_create(lv_scr_act(), nullptr)) {};

        template<typename T>
        explicit Label(const Object <T> &parent) noexcept
                : Object(lv_label_create(parent.raw(), nullptr)) {}

        template<typename T>
        explicit Label(const Object <T> &parent, const Label &copy) noexcept
                : Object(lv_label_create(parent.raw(), copy.raw())) {}

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
            lv_label_set_text(raw(), text);
            return this->underlying();
        }

        template<typename ... Args>
        Label &text_fmt(const char *text, Args &&... args) {
            lv_label_set_text_fmt(raw(), text, std::forward<Args>(args)...);
            return this->underlying();
        }

        Label &text_static(const char *text) {
            lv_label_set_text_static(raw(), text);
            return this->underlying();
        }

        Label &long_mode(LabelLongMode mode) {
            lv_label_set_long_mode(raw(), static_cast<lv_label_long_mode_t>(mode));
            return this->underlying();
        }

        using Object::align;

        Label &align(const LabelAlign align) {
            lv_label_set_align(raw(), static_cast<lv_label_align_t>(align));
            return this->underlying();
        }

        Label &recolor(bool enabled) {
            lv_label_set_recolor(raw(), enabled);
            return this->underlying();
        }

        Label &anim_speed(uint16_t speed) {
            lv_label_set_anim_speed(raw(), speed);
            return this->underlying();
        }

        Label &text_sel_start(uint32_t index) {
            lv_label_set_text_sel_start(raw(), index);
            return this->underlying();
        }

        Label &text_sel_end(uint32_t index) {
            lv_label_set_text_sel_end(raw(), index);
            return this->underlying();
        }

        [[nodiscard]] char *text() const {
            return lv_label_get_text(raw());
        }

        [[nodiscard]] LabelLongMode long_mode() const {
            return static_cast<LabelLongMode>(lv_label_get_long_mode(raw()));
        }

        [[nodiscard]] LabelAlign align() const {
            return static_cast<LabelAlign>(lv_label_get_align(raw()));
        }

        bool recolor() {
            return lv_label_get_recolor(raw());
        }

        uint16_t anim_speed() {
            return lv_label_get_anim_speed(raw());
        }

        lv_point_t letter_pos(uint32_t index) {
            lv_point_t point;
            lv_label_get_letter_pos(raw(), index, &point);
            return point;
        }

        uint32_t letter_on(lv_point_t &point) {
            return lv_label_get_letter_on(raw(), &point);
        }

        bool is_char_under_pos(lv_point_t &point) {
            return lv_label_is_char_under_pos(raw(), &point);
        }

        uint32_t text_sel_start() {
            return lv_label_get_text_sel_start(raw());
        }

        uint32_t text_sel_end() {
            return lv_label_get_text_sel_end(raw());
        }

        auto &ins_text(uint32_t pos, const char *text) {
            lv_label_ins_text(raw(), pos, text);
            return this->underlying();
        }

        auto &cut_text(uint32_t pos, uint32_t count) {
            lv_label_cut_text(raw(), pos, count);
            return this->underlying();
        }
    };

}

#endif // LV_USE_LABEL
