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

    /* constexpr bool strings_equal(char const *a, char const *b) {
         return *a == *b && (*a == '\0' || strings_equal(a + 1, b + 1));
     }


     template<size_t WIDTH>
     using StringArray = std::array<const char *, WIDTH>;

     template<size_t WIDTH>
     static constexpr bool valid(const StringArray<WIDTH> &array) {
         return !std::ranges::any_of(array, [](const char *string) {
             return strings_equal(string, "") || strings_equal(string, "\n");
         });
     }

     template<size_t WIDTH, size_t HEIGHT>
     using StringMatrix = std::array<const StringArray<WIDTH>, HEIGHT>;

     template<size_t WIDTH, size_t HEIGHT>
     static constexpr bool valid(const StringMatrix<WIDTH, HEIGHT> &matrix) {
         return std::ranges::all_of(matrix, [](const StringArray<WIDTH> &array) {
             return valid(array);
         });
     }

     template<size_t WIDTH, size_t HEIGHT>
     using ButtonControlMap = std::array<lv_btnmatrix_ctrl_t, WIDTH * HEIGHT>;

     template<size_t WIDTH, size_t HEIGHT>
     class ButtonMap {
     public:
         explicit constexpr ButtonMap(const StringMatrix<WIDTH, HEIGHT> &input) {
             for (int row = 0; row < HEIGHT; ++row) {
                 for (int col = 0; col < WIDTH + 1; ++col) {
                     if (col == WIDTH) {
                         if (row == HEIGHT - 1) {
                             map[row * (WIDTH + 1) + col] = END;
                         } else {
                             map[row * (WIDTH + 1) + col] = NEW_LINE;
                         }
                     } else {
                         map[row * (WIDTH + 1) + col] = input[row][col];
                     }
                 }
             }
         }

         auto data() const {
             return map.data();
         }

         constexpr auto width() const {
             return WIDTH;
         }

         constexpr auto height() const {
             return HEIGHT;
         }

     private:
         static constexpr const char *NEW_LINE = "\n";
         static constexpr const char *END = "";
         StringArray<WIDTH * (HEIGHT + 1)> map;
     };*/

    class ButtonMatrix final : public Object<ButtonMatrix> {
    public:
        ButtonMatrix() : Object(lv_btnmatrix_create(lv_scr_act(), nullptr)) {}

        /*
         * SETTERS
         */
        ButtonMatrix &map(std::span<const char *> map) {
            lv_btnmatrix_set_map(get(), map.data());
            return this->underlying();
        }

//        ButtonMatrix &map(const ButtonMap<WIDTH, HEIGHT> &map) {
//            lv_btnmatrix_set_map(get(), const_cast<const char **>(map.data()));
//            return this->underlying();
//        }

        ButtonMatrix &ctrl_map(std::span<lv_btnmatrix_ctrl_t> map) {
            lv_btnmatrix_set_ctrl_map(get(), map.data());
            return this->underlying();
        }

        ButtonMatrix &focused_btn(uint16_t id) {
            lv_btnmatrix_set_focused_btn(get(), id);
            return this->underlying();
        }

        ButtonMatrix &recolor(bool enabled) {
            lv_btnmatrix_set_recolor(get(), enabled);
            return this->underlying();
        }

        ButtonMatrix &set_btn_ctrl(uint16_t btn_id, lv_btnmatrix_ctrl_t ctrl) {
            lv_btnmatrix_set_btn_ctrl(get(), btn_id, ctrl);
            return this->underlying();
        }

        ButtonMatrix &clear_btn_ctrl(uint16_t btn_id, lv_btnmatrix_ctrl_t ctrl) {
            lv_btnmatrix_clear_btn_ctrl(get(), btn_id, ctrl);
            return this->underlying();
        }

        ButtonMatrix &set_btn_ctr_all(lv_btnmatrix_ctrl_t ctrl) {
            lv_btnmatrix_set_btn_ctrl_all(get(), ctrl);
            return this->underlying();
        }

        ButtonMatrix &clear_btn_ctr_all(lv_btnmatrix_ctrl_t ctrl) {
            lv_btnmatrix_clear_btn_ctrl_all(get(), ctrl);
            return this->underlying();
        }

        ButtonMatrix &btn_width(uint16_t btn_id, uint8_t width) {
            lv_btnmatrix_set_btn_width(get(), btn_id, width);
            return this->underlying();
        }

        ButtonMatrix &one_check(bool one_check) {
            lv_btnmatrix_set_one_check(get(), one_check);
            return this->underlying();
        }

        using Object::align;

        ButtonMatrix &align(LabelAlign align) {
            lv_btnmatrix_set_align(get(), static_cast<lv_label_align_t>(align));
            return this->underlying();
        }

        /*
         * GETTERS
         */
        [[nodiscard]] const char **map_array() const {
            return lv_btnmatrix_get_map_array(get());
        }

        [[nodiscard]] bool recolor() const{
            return lv_btnmatrix_get_recolor(get());
        }

        [[nodiscard]] uint16_t active_btn() const{
            return lv_btnmatrix_get_active_btn(get());
        }

        [[nodiscard]] const char *active_btn_text() const{
            return lv_btnmatrix_get_active_btn_text(get());
        }

        [[nodiscard]] uint16_t focused_btn() const{
            return lv_btnmatrix_get_focused_btn(get());
        }

        [[nodiscard]] const char *btn_text(uint16_t id) const{
            return lv_btnmatrix_get_active_btn_text(get());
        }

        [[nodiscard]] bool btn_ctrl(uint16_t id, lv_btnmatrix_ctrl_t ctrl) const{
            return lv_btnmatrix_get_btn_ctrl(get(), id, ctrl);
        }

        [[nodiscard]] bool one_check() const {
            return lv_btnmatrix_get_one_check(get());
        }

        [[nodiscard]] LabelAlign align() const {
            return static_cast<LabelAlign>(lv_btnmatrix_get_align(get()));
        }
    };
}

#endif // LV_USE_BTNMATRIX
