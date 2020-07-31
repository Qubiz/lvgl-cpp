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
        KNOB  = LV_CPICKER_PART_KNOB,
    };
    
    class ColorPicker final : public Object<ColorPicker> {
    public:

        ColorPicker() : Object(lv_cpicker_create(lv_scr_act(), nullptr)) {}

        /*
         * SETTERS
         */

        ColorPicker & type(ColorPickerType type) {
            lv_cpicker_set_type(get(), static_cast<lv_cpicker_type_t>(type));
            return this->underlying();
        }
        ColorPicker & hue(uint16_t hue) {
            lv_cpicker_set_hue(get(), hue);
            return this->underlying();
        }
        ColorPicker & saturation(uint8_t saturation) {
            lv_cpicker_set_saturation(get(), saturation);
            return this->underlying();
        }
        ColorPicker & value(uint8_t val) {
            lv_cpicker_set_value(get(), val);
            return this->underlying();
        }
        ColorPicker & hsv(lv_color_hsv_t hsv) {
            lv_cpicker_set_hsv(get(), hsv);
            return this->underlying();
        }
        ColorPicker & color(lv_color_t color) {
            lv_cpicker_set_color(get(), color);
            return this->underlying();
        }
        ColorPicker & color_mode(ColorPickerMode mode) {
            lv_cpicker_set_color_mode(get(), static_cast<lv_cpicker_color_mode_t>(mode));
            return this->underlying();
        }
        ColorPicker & color_mode_fixed(bool fixed) {
            lv_cpicker_set_color_mode_fixed(get(), fixed);
            return this->underlying();
        }
        ColorPicker & knob_colored(bool en) {
            lv_cpicker_set_knob_colored(get(), en);
            return this->underlying();
        }
        
        /*
         * GETTERS
         */
        [[nodiscard]] ColorPickerMode color_mode() const {
            return static_cast<ColorPickerMode>(lv_cpicker_get_color_mode(get()));
        }
        [[nodiscard]] bool color_mode_fixed() const {
            return lv_cpicker_get_color_mode_fixed(get());
        }
        [[nodiscard]] uint16_t hue() const {
            return lv_cpicker_get_hue(get());
        }
        [[nodiscard]] uint8_t saturation() const {
            return lv_cpicker_get_saturation(get());
        }
        [[nodiscard]] uint8_t value() const {
            return lv_cpicker_get_value(get());
        }
        [[nodiscard]] lv_color_hsv_t hsv() const {
            return lv_cpicker_get_hsv(get());
        }
        [[nodiscard]] lv_color_t color() const {
            return lv_cpicker_get_color(get());
        }
        [[nodiscard]] bool knob_colored() const {
            return lv_cpicker_get_knob_colored(get());
        }

    };
}

#endif // LV_USE_CPICKER