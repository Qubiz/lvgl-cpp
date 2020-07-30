#pragma once

#include "Object.h"

#if LV_USE_TABLE && LV_USE_LABEL

#include "Label.h"

namespace lvglcpp {

    enum class TablePart : uint8_t {
        BG = LV_TABLE_PART_BG,
        CELL1 = LV_TABLE_PART_CELL1,
        CELL2 = LV_TABLE_PART_CELL2,
        CELL3 = LV_TABLE_PART_CELL3,
        CELL4 = LV_TABLE_PART_CELL4,
    };
    
    class Table final : public Object<Table> {
    public:

        Table() : Object(lv_table_create(lv_scr_act(), nullptr)) {}

        /*
         * SETTERS
         */
        Table & cell_value(uint16_t row, uint16_t col, const char * txt) {
            lv_table_set_cell_value(get(), row, col, txt);
            return this->underlying();
        }
        Table & row_cnt(uint16_t row_cnt) {
            lv_table_set_row_cnt(get(), row_cnt);
            return this->underlying();
        }
        Table & col_cnt(uint16_t col_cnt) {
            lv_table_set_col_cnt(get(), col_cnt);
            return this->underlying();
        }
        Table & col_width(uint16_t col_id, lv_coord_t w) {
            lv_table_set_col_width(get(), col_id, w);
            return this->underlying();
        }
        Table & cell_align(uint16_t row, uint16_t col, LabelAlign align) {
            lv_table_set_cell_align(get(), row, col, static_cast<lv_label_align_t>(align));
            return this->underlying();
        }
        Table & cell_type(uint16_t row, uint16_t col, uint8_t type) {
            lv_table_set_cell_type(get(), row, col, type);
            return this->underlying();
        }
        Table & cell_crop(uint16_t row, uint16_t col, bool crop) {
            lv_table_set_cell_crop(get(), row, col, crop);
            return this->underlying();
        }
        Table & cell_merge_right(uint16_t row, uint16_t col, bool en) {
            lv_table_set_cell_merge_right(get(), row, col, en);
            return this->underlying();
        }

        /*
         * GETTERS
         */

        [[nodiscard]] const char * cell_value(uint16_t row, uint16_t col) const {
            return lv_table_get_cell_value(get(), row, col);
        }
        [[nodiscard]] uint16_t row_cnt() const {
            return lv_table_get_row_cnt(get());
        }
        [[nodiscard]] uint16_t col_cnt() const {
            return lv_table_get_col_cnt(get());
        }
        [[nodiscard]] lv_coord_t col_width(uint16_t col_id) const {
            return lv_table_get_col_width(get(), col_id);
        }
        [[nodiscard]] lv_label_align_t cell_align(uint16_t row, uint16_t col) const {
            return lv_table_get_cell_align(get(), row, col);
        }
        [[nodiscard]] lv_label_align_t cell_type(uint16_t row, uint16_t col) const {
            return lv_table_get_cell_type(get(), row, col);
        }
        [[nodiscard]] lv_label_align_t cell_crop(uint16_t row, uint16_t col) const {
            return lv_table_get_cell_crop(get(), row, col);
        }
        [[nodiscard]] bool cell_merge_right(uint16_t row, uint16_t col) const {
            return lv_table_get_cell_merge_right(get(), row, col);
        }
        [[nodiscard]] lv_res_t pressed_cell(uint16_t * row, uint16_t * col) const {
            return lv_table_get_pressed_cell(get(), row, col);
        }
        
    };
}

#endif // LV_USE_TABLE