#pragma once

#include "Object.h"

#if LV_USE_CALENDAR

#include <span>

namespace lvglcpp {

    enum class CalendarPart : lv_calendar_part_t {
        BG = LV_CALENDAR_PART_BG, /**< Background and "normal" date numbers style */
        HEADER = LV_CALENDAR_PART_HEADER, /** Calendar header style */
        DAY_NAMES = LV_CALENDAR_PART_DAY_NAMES, /** Day name style */
        DATE = LV_CALENDAR_PART_DATE, /** Day name style */
    };

    class Calendar final : public Object<Calendar> {
    public:

        Calendar() : Object(lv_calendar_create(lv_scr_act(), nullptr)) {}

        /*
         * SETTERS
         */

        Calendar &today_date(lv_calendar_date_t &&today) {
            lv_calendar_set_today_date(get(), &today);
            return this->underlying();
        };

        Calendar &today_date(lv_calendar_date_t &today) {
            lv_calendar_set_today_date(get(), &today);
            return this->underlying();
        };

        Calendar &showed_date(lv_calendar_date_t &&showed) {
            lv_calendar_set_showed_date(get(), &showed);
            return this->underlying();
        };

        Calendar &showed_date(lv_calendar_date_t &showed) {
            lv_calendar_set_showed_date(get(), &showed);
            return this->underlying();
        };

        Calendar &highlighted_dates(std::span<lv_calendar_date_t> highlighted) {
            lv_calendar_set_highlighted_dates(get(), highlighted.data(), highlighted.size());
            return this->underlying();
        };

        Calendar &day_names(std::span<const char *, 7> day_names) {
            lv_calendar_set_day_names(get(), day_names.data());
            return this->underlying();
        };

        Calendar &month_names(std::span<const char *, 12> month_names) {
            lv_calendar_set_month_names(get(), month_names.data());
            return this->underlying();
        };

        /*
         * GETTERS
         */
        [[nodiscard]] lv_calendar_date_t &today_date() const {
            return *lv_calendar_get_today_date(get());
        };

        [[nodiscard]] lv_calendar_date_t &showed_date() const {
            return *lv_calendar_get_showed_date(get());
        };

        [[nodiscard]] lv_calendar_date_t &pressed_date() const {
            return *lv_calendar_get_pressed_date(get());
        };

        [[nodiscard]] std::span<lv_calendar_date_t> highlighted_dates() const {
            return std::span(lv_calendar_get_highlighted_dates(get()),
                             lv_calendar_get_highlighted_dates_num(get()));
        }

        [[nodiscard]] std::span<const char *,7> day_names() const {
            return std::span<const char *, 7>(lv_calendar_get_day_names(get()), 7);
        };

        [[nodiscard]] std::span<const char *,12>month_names() const {
            return std::span<const char *, 12>(lv_calendar_get_month_names(get()), 7);
        };
    };
}

#endif // LV_USE_CALENDAR