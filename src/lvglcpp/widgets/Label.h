#pragma once

#ifndef LVGL_CPP_LABEL_H
#define LVGL_CPP_LABEL_H

#include <lvgl.h>

#if LV_USE_LABEL

#include "Object.h"

namespace lvglcpp {

    enum class LabelAlign : lv_label_align_t {
        AUTO = LV_LABEL_ALIGN_AUTO,
        LEFT = LV_LABEL_ALIGN_LEFT,
        RIGHT = LV_LABEL_ALIGN_RIGHT,
        CENTER = LV_LABEL_ALIGN_CENTER
    };

    enum class LabelLongMode : lv_label_long_mode_t {
        LONG_EXPAND = LV_LABEL_LONG_EXPAND,
        LONG_BREAK = LV_LABEL_LONG_BREAK,
        LONG_DOT = LV_LABEL_LONG_DOT,
        LONG_SROLL = LV_LABEL_LONG_SROLL,
        LONG_SROLL_CIRC = LV_LABEL_LONG_SROLL_CIRC,
        LONG_CROP = LV_LABEL_LONG_CROP,
    };

    enum class LabelPart : lv_obj_part_t {
        MAIN = LV_LABEL_PART_MAIN,
    };

    class Label final : public Object<Label> {
    public:

        Label() : Object(lv_label_create(lv_scr_act(), nullptr)) {}

        explicit Label(const char *text) : Object(lv_label_create(lv_scr_act(), nullptr)) {
            set_text(text);
        }

        Label &set_text(const char *text) {
            lv_label_set_text(get(), text);
            return this->underlying();
        }

        template<typename ... Args>
        Label &set_text_fmt(const char *text, const Args &... args) {
            lv_label_set_text_fmt(get(), text, args...);
            return this->underlying();
        }

        Label &set_text_static(const char *text) {
            lv_label_set_text_static(get(), text);
            return this->underlying();
        }

        Label &set_long_mode(LabelLongMode mode) {
            lv_label_set_long_mode(get(), static_cast<lv_label_long_mode_t>(mode));
            return this->underlying();
        }

        Label &set_align(const LabelAlign align) {
            lv_label_set_align(get(), static_cast<lv_label_align_t>(align));
            return this->underlying();
        }

        Label &set_recolor(bool enabled) {
            lv_label_set_recolor(get(), enabled);
            return this->underlying();
        }

        Label &set_anim_speed(uint16_t speed) {
            lv_label_set_anim_speed(get(), speed);
            return this->underlying();
        }

        Label &set_text_sel_start(uint32_t index) {
            lv_label_set_text_sel_start(get(), index);
            return this->underlying();
        }

        Label &set_text_sel_end(uint32_t index) {
            lv_label_set_text_sel_end(get(), index);
            return this->underlying();
        }

        [[nodiscard]] char *get_text() const {
            return lv_label_get_text(get());
        }

        [[nodiscard]] LabelLongMode get_long_mode() const {
            return static_cast<LabelLongMode>(lv_label_get_long_mode(get()));
        }

        [[nodiscard]] LabelAlign get_align() const {
            return static_cast<LabelAlign>(lv_label_get_align(get()));
        }

        bool get_recolor() {
            return lv_label_get_recolor(get());
        }

        uint16_t get_anim_speed() {
            return lv_label_get_anim_speed(get());
        }

        lv_point_t get_letter_pos(uint32_t index) {
            lv_point_t point;
            lv_label_get_letter_pos(get(), index, &point);
            return point;
        }

        uint32_t get_letter_on(lv_point_t &point) {
            return lv_label_get_letter_on(get(), &point);
        }

        bool is_char_under_pos(lv_point_t &point) {
            return lv_label_is_char_under_pos(get(), &point);
        }

        uint32_t get_text_sel_start() {
            return lv_label_get_text_sel_start(get());
        }

        uint32_t get_text_sel_end() {
            return lv_label_get_text_sel_end(get());
        }

        lv_style_list_t *get_style(LabelPart type) {
            return lv_label_get_style(get(), static_cast<lv_label_part_t>(type));
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

#endif //LVGL_CPP_LABEL_H
