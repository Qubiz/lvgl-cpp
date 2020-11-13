#pragma once

#include "Object.h"

#if LV_USE_CPICKER

namespace lvglcpp {

    enum class ColorPickerType : lv_cpicker_type_t {
        RECT = LV_CPICKER_TYPE_RECT,
        DISC = LV_CPICKER_TYPE_DISC,
    };

    enum class ColorPickerMode : lv_cpicker_color_mode_t {
        HUE = LV_CPICKER_COLOR_MODE_HUE,
        SATURATION = LV_CPICKER_COLOR_MODE_SATURATION,
        VALUE = LV_CPICKER_COLOR_MODE_VALUE,
    };

    enum class ColorPickerPart {
        MAIN = LV_CPICKER_PART_MAIN,
        KNOB = LV_CPICKER_PART_KNOB,
    };

    class ColorPicker : public Object<ColorPicker> {
    protected:
        explicit ColorPicker(lv_obj_t *other) noexcept: Object(other) {};

    public:

        ColorPicker() noexcept: Object(lv_cpicker_create(lv_scr_act(), nullptr)) {};

        template<typename T>
        explicit ColorPicker(const Object <T> &parent) noexcept
                : Object(lv_cpicker_create(parent.raw(), nullptr)) {}

        template<typename T>
        explicit ColorPicker(const Object <T> &parent, const ColorPicker &copy) noexcept
                : Object(lv_cpicker_create(parent.raw(), copy.raw())) {}

        /*
         * SETTERS
         */

        ColorPicker &type(ColorPickerType type) {
            lv_cpicker_set_type(raw(), static_cast<lv_cpicker_type_t>(type));
            return this->underlying();
        }

        ColorPicker &hue(uint16_t hue) {
            lv_cpicker_set_hue(raw(), hue);
            return this->underlying();
        }

        ColorPicker &saturation(uint8_t saturation) {
            lv_cpicker_set_saturation(raw(), saturation);
            return this->underlying();
        }

        ColorPicker &value(uint8_t val) {
            lv_cpicker_set_value(raw(), val);
            return this->underlying();
        }

        ColorPicker &hsv(lv_color_hsv_t hsv) {
            lv_cpicker_set_hsv(raw(), hsv);
            return this->underlying();
        }

        ColorPicker &color(lv_color_t color) {
            lv_cpicker_set_color(raw(), color);
            return this->underlying();
        }

        ColorPicker &color_mode(ColorPickerMode mode) {
            lv_cpicker_set_color_mode(raw(), static_cast<lv_cpicker_color_mode_t>(mode));
            return this->underlying();
        }

        ColorPicker &color_mode_fixed(bool fixed) {
            lv_cpicker_set_color_mode_fixed(raw(), fixed);
            return this->underlying();
        }

        ColorPicker &knob_colored(bool en) {
            lv_cpicker_set_knob_colored(raw(), en);
            return this->underlying();
        }

        /*
         * GETTERS
         */
        [[nodiscard]] ColorPickerMode color_mode() const {
            return static_cast<ColorPickerMode>(lv_cpicker_get_color_mode(raw()));
        }

        [[nodiscard]] bool color_mode_fixed() const {
            return lv_cpicker_get_color_mode_fixed(raw());
        }

        [[nodiscard]] uint16_t hue() const {
            return lv_cpicker_get_hue(raw());
        }

        [[nodiscard]] uint8_t saturation() const {
            return lv_cpicker_get_saturation(raw());
        }

        [[nodiscard]] uint8_t value() const {
            return lv_cpicker_get_value(raw());
        }

        [[nodiscard]] lv_color_hsv_t hsv() const {
            return lv_cpicker_get_hsv(raw());
        }

        [[nodiscard]] lv_color_t color() const {
            return lv_cpicker_get_color(raw());
        }

        [[nodiscard]] bool knob_colored() const {
            return lv_cpicker_get_knob_colored(raw());
        }

    };
}

#endif // LV_USE_CPICKER