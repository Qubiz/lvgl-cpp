#pragma once

#include "Label.h"

#if LV_USE_BTNMATRIX

#include <span>

namespace lvglcpp {

    enum class ButtonMatrixControl : lv_btnmatrix_ctrl_t {
        HIDDEN = LV_BTNMATRIX_CTRL_HIDDEN,
        NO_REPEAT = LV_BTNMATRIX_CTRL_NO_REPEAT,
        DISABLED = LV_BTNMATRIX_CTRL_DISABLED,
        CHECKABLE = LV_BTNMATRIX_CTRL_CHECKABLE,
        CHECK_STATE = LV_BTNMATRIX_CTRL_CHECK_STATE,
        CLICK_TRIG = LV_BTNMATRIX_CTRL_CLICK_TRIG,
    };

    enum class ButtonMatrixPart {
        BG = LV_BTNMATRIX_PART_BG,
        BTN = LV_BTNMATRIX_PART_BTN
    };

    class ButtonMatrix : public Object<ButtonMatrix> {
    protected:
        explicit ButtonMatrix(lv_obj_t *other) noexcept: Object(other) {};

    public:

        ButtonMatrix() noexcept: Object(lv_btnmatrix_create(lv_scr_act(), nullptr)) {};

        template<typename T>
        explicit ButtonMatrix(const Object<T> &parent) noexcept
                : Object(lv_btnmatrix_create(parent.raw(), nullptr)) {}

        template<typename T>
        explicit ButtonMatrix(const Object<T> &parent, const ButtonMatrix &copy) noexcept
                : Object(lv_btnmatrix_create(parent.raw(), copy.raw())) {}

        /*
         * SETTERS
         */
        ButtonMatrix &map(std::span<const char *> map) {
            lv_btnmatrix_set_map(raw(), map.data());
            return this->underlying();
        }

//        ButtonMatrix &map(const ButtonMap<WIDTH, HEIGHT> &map) {
//            lv_btnmatrix_set_map(get(), const_cast<const char **>(map.data()));
//            return this->underlying();
//        }

        ButtonMatrix &ctrl_map(std::span<lv_btnmatrix_ctrl_t> map) {
            lv_btnmatrix_set_ctrl_map(raw(), map.data());
            return this->underlying();
        }

        ButtonMatrix &focused_btn(uint16_t id) {
            lv_btnmatrix_set_focused_btn(raw(), id);
            return this->underlying();
        }

        ButtonMatrix &recolor(bool enabled) {
            lv_btnmatrix_set_recolor(raw(), enabled);
            return this->underlying();
        }

        ButtonMatrix &set_btn_ctrl(uint16_t btn_id, lv_btnmatrix_ctrl_t ctrl) {
            lv_btnmatrix_set_btn_ctrl(raw(), btn_id, ctrl);
            return this->underlying();
        }

        ButtonMatrix &clear_btn_ctrl(uint16_t btn_id, lv_btnmatrix_ctrl_t ctrl) {
            lv_btnmatrix_clear_btn_ctrl(raw(), btn_id, ctrl);
            return this->underlying();
        }

        ButtonMatrix &set_btn_ctr_all(lv_btnmatrix_ctrl_t ctrl) {
            lv_btnmatrix_set_btn_ctrl_all(raw(), ctrl);
            return this->underlying();
        }

        ButtonMatrix &clear_btn_ctr_all(lv_btnmatrix_ctrl_t ctrl) {
            lv_btnmatrix_clear_btn_ctrl_all(raw(), ctrl);
            return this->underlying();
        }

        ButtonMatrix &btn_width(uint16_t btn_id, uint8_t width) {
            lv_btnmatrix_set_btn_width(raw(), btn_id, width);
            return this->underlying();
        }

        ButtonMatrix &one_check(bool one_check) {
            lv_btnmatrix_set_one_check(raw(), one_check);
            return this->underlying();
        }

        using Object::align;

        ButtonMatrix &align(LabelAlign align) {
            lv_btnmatrix_set_align(raw(), static_cast<lv_label_align_t>(align));
            return this->underlying();
        }

        /*
         * GETTERS
         */
        [[nodiscard]] const char **map_array() const {
            return lv_btnmatrix_get_map_array(raw());
        }

        [[nodiscard]] bool recolor() const {
            return lv_btnmatrix_get_recolor(raw());
        }

        [[nodiscard]] uint16_t active_btn() const {
            return lv_btnmatrix_get_active_btn(raw());
        }

        [[nodiscard]] const char *active_btn_text() const {
            return lv_btnmatrix_get_active_btn_text(raw());
        }

        [[nodiscard]] uint16_t focused_btn() const {
            return lv_btnmatrix_get_focused_btn(raw());
        }

        [[nodiscard]] const char *btn_text(uint16_t id) const {
            return lv_btnmatrix_get_active_btn_text(raw());
        }

        [[nodiscard]] bool btn_ctrl(uint16_t id, lv_btnmatrix_ctrl_t ctrl) const {
            return lv_btnmatrix_get_btn_ctrl(raw(), id, ctrl);
        }

        [[nodiscard]] bool one_check() const {
            return lv_btnmatrix_get_one_check(raw());
        }

        [[nodiscard]] LabelAlign align() const {
            return static_cast<LabelAlign>(lv_btnmatrix_get_align(raw()));
        }
    };
}

#endif // LV_USE_BTNMATRIX
