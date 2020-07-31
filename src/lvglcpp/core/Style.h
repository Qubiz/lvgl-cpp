#pragma once

#ifndef LVGL_CPP_STYLE_H
#define LVGL_CPP_STYLE_H

#include <lvgl.h>

namespace lvglcpp {

    enum class ObjectState {
        DEFAULT = LV_STATE_DEFAULT,
        CHECKED = LV_STATE_CHECKED,
        FOCUSED = LV_STATE_FOCUSED,
        EDITED = LV_STATE_EDITED,
        HOVERED = LV_STATE_HOVERED,
        PRESSED = LV_STATE_PRESSED,
        DISABLED = LV_STATE_DISABLED,
    };

    namespace detail {

        template<typename ValueType>
        using LocalStylePropertySetter = void (*)(lv_obj_t *obj, uint8_t part, lv_state_t state, ValueType value);

        template<typename ValueType>
        using StylePropertySetter = void (*)(lv_style_t *style, lv_state_t state, ValueType value);
        
        template<typename ValueType>
        using StylePropertyGetter = ValueType (*)(const lv_obj_t *obj, uint8_t part);

        template<typename ValueType, 
                const lv_style_property_t STYLE_PROPERTY,
                const StylePropertySetter<ValueType> SET_FUNC,
                const LocalStylePropertySetter<ValueType> LOCAL_SET_FUNC, 
                const StylePropertyGetter<ValueType> GET_FUNC>
        struct StyleProperty {
            using value_type = ValueType;
            static constexpr lv_style_property_t enum_value = STYLE_PROPERTY;
            static constexpr inline void set_value(lv_obj_t *obj, value_type value, uint8_t part, lv_state_t state) {
                return LOCAL_SET_FUNC(obj, part, state, value);
            }

            static constexpr inline void set_value(lv_style_t * style, lv_state_t state, value_type value) {
                return SET_FUNC(style, state, value);
            }

            static constexpr inline value_type get_value(const lv_obj_t *obj, uint8_t part) {
                return GET_FUNC(obj, part);
            }

//            static constexpr inline lv_style_property_t enum_value() {
//                return STYLE_PROPERTY;
//            }
        };

        template<typename ValueType,
                const StylePropertySetter<ValueType> SET_FUNC,
                const LocalStylePropertySetter<ValueType> LOCAL_SET_FUNC>
        struct SettableStyleProperty {
            using value_type = ValueType;

            static constexpr inline void set_value(lv_obj_t *obj, value_type value, uint8_t part, lv_state_t state) {
                return LOCAL_SET_FUNC(obj, part, state, value);
            }

            static constexpr inline void set_value(lv_style_t * style, lv_state_t state, value_type value) {
                return SET_FUNC(style, state, value);
            }

        };

        template<const lv_style_property_t STYLE_PROPERTY,
                const detail::StylePropertySetter<lv_opa_t> SET_FUNC,
                const detail::LocalStylePropertySetter<lv_opa_t> LOCAL_SET_FUNC,
                const detail::StylePropertyGetter<lv_opa_t> GET_FUNC>
        using Opacity = detail::StyleProperty<lv_opa_t, STYLE_PROPERTY, SET_FUNC, LOCAL_SET_FUNC, GET_FUNC>;

        template<const lv_style_property_t STYLE_PROPERTY,
                const detail::StylePropertySetter<lv_style_int_t> SET_FUNC,
                const detail::LocalStylePropertySetter<lv_style_int_t> LOCAL_SET_FUNC,
                const detail::StylePropertyGetter<lv_style_int_t> GET_FUNC>
        using Integer = detail::StyleProperty<lv_style_int_t, STYLE_PROPERTY, SET_FUNC, LOCAL_SET_FUNC, GET_FUNC>;

        template<const detail::StylePropertySetter<lv_style_int_t> SET_FUNC,
                const detail::LocalStylePropertySetter<lv_style_int_t> LOCAL_SET_FUNC>
        using SettableInteger = detail::SettableStyleProperty<lv_style_int_t, SET_FUNC, LOCAL_SET_FUNC>;

        template<const lv_style_property_t STYLE_PROPERTY,
                const detail::StylePropertySetter<bool> SET_FUNC,
                const detail::LocalStylePropertySetter<bool> LOCAL_SET_FUNC,
                const detail::StylePropertyGetter<bool> GET_FUNC>
        using Bool = detail::StyleProperty<bool, STYLE_PROPERTY, SET_FUNC, LOCAL_SET_FUNC, GET_FUNC>;

        template<const lv_style_property_t STYLE_PROPERTY,
                const detail::StylePropertySetter<lv_blend_mode_t> SET_FUNC,
                const detail::LocalStylePropertySetter<lv_blend_mode_t> LOCAL_SET_FUNC,
                const detail::StylePropertyGetter<lv_blend_mode_t> GET_FUNC>
        using BlendMode = detail::StyleProperty<lv_blend_mode_t, STYLE_PROPERTY, SET_FUNC, LOCAL_SET_FUNC, GET_FUNC>;

        template<const lv_style_property_t STYLE_PROPERTY,
                const detail::StylePropertySetter<lv_color_t> SET_FUNC,
                const detail::LocalStylePropertySetter<lv_color_t> LOCAL_SET_FUNC,
                const detail::StylePropertyGetter<lv_color_t> GET_FUNC>
        using Color = detail::StyleProperty<lv_color_t, STYLE_PROPERTY, SET_FUNC, LOCAL_SET_FUNC, GET_FUNC>;

        template<const lv_style_property_t STYLE_PROPERTY,
                const detail::StylePropertySetter<const lv_font_t *> SET_FUNC,
                const detail::LocalStylePropertySetter<const lv_font_t *> LOCAL_SET_FUNC,
                const detail::StylePropertyGetter<const lv_font_t *> GET_FUNC>
        using Font = detail::StyleProperty<const lv_font_t *, STYLE_PROPERTY, SET_FUNC, LOCAL_SET_FUNC, GET_FUNC>;

        template<const lv_style_property_t STYLE_PROPERTY,
                const detail::StylePropertySetter<const char *> SET_FUNC,
                const detail::LocalStylePropertySetter<const char *> LOCAL_SET_FUNC,
                const detail::StylePropertyGetter<const char *> GET_FUNC>
        using String = detail::StyleProperty<const char *, STYLE_PROPERTY, SET_FUNC, LOCAL_SET_FUNC, GET_FUNC>;

        template<const lv_style_property_t STYLE_PROPERTY,
                const detail::StylePropertySetter<const void *> SET_FUNC,
                const detail::LocalStylePropertySetter<const void *> LOCAL_SET_FUNC,
                const detail::StylePropertyGetter<const void *> GET_FUNC>
        using Image = detail::StyleProperty<const void *, STYLE_PROPERTY, SET_FUNC, LOCAL_SET_FUNC, GET_FUNC>;

        template<const lv_style_property_t STYLE_PROPERTY,
                const detail::StylePropertySetter<lv_border_side_t> SET_FUNC,
                const detail::LocalStylePropertySetter<lv_border_side_t> LOCAL_SET_FUNC,
                const detail::StylePropertyGetter<lv_border_side_t> GET_FUNC>
        using BorderSide = detail::StyleProperty<lv_border_side_t, STYLE_PROPERTY, SET_FUNC, LOCAL_SET_FUNC, GET_FUNC>;

        template<const lv_style_property_t STYLE_PROPERTY,
                const detail::StylePropertySetter<lv_grad_dir_t> SET_FUNC,
                const detail::LocalStylePropertySetter<lv_grad_dir_t> LOCAL_SET_FUNC,
                const detail::StylePropertyGetter<lv_grad_dir_t> GET_FUNC>
        using GradDir = detail::StyleProperty<lv_grad_dir_t, STYLE_PROPERTY, SET_FUNC, LOCAL_SET_FUNC, GET_FUNC>;

        template<const lv_style_property_t STYLE_PROPERTY,
                const detail::StylePropertySetter<lv_align_t> SET_FUNC,
                const detail::LocalStylePropertySetter<lv_align_t> LOCAL_SET_FUNC,
                const detail::StylePropertyGetter<lv_align_t> GET_FUNC>
        using Align = detail::StyleProperty<lv_align_t, STYLE_PROPERTY, SET_FUNC, LOCAL_SET_FUNC, GET_FUNC>;

        template<const lv_style_property_t STYLE_PROPERTY,
                const detail::StylePropertySetter<lv_text_decor_t> SET_FUNC,
                const detail::LocalStylePropertySetter<lv_text_decor_t> LOCAL_SET_FUNC,
                const detail::StylePropertyGetter<lv_text_decor_t> GET_FUNC>
        using TextDecor = detail::StyleProperty<lv_text_decor_t, STYLE_PROPERTY, SET_FUNC, LOCAL_SET_FUNC, GET_FUNC>;

#if LV_USE_ANIMATION
        template<const lv_style_property_t STYLE_PROPERTY,
                const detail::StylePropertySetter<lv_anim_path_t *> SET_FUNC,
                const detail::LocalStylePropertySetter<lv_anim_path_t *> LOCAL_SET_FUNC,
                const detail::StylePropertyGetter<lv_anim_path_t *> GET_FUNC>
        using AnimPath = detail::StyleProperty<lv_anim_path_t *, STYLE_PROPERTY, SET_FUNC, LOCAL_SET_FUNC, GET_FUNC>;
#else
        template<const lv_style_property_t STYLE_PROPERTY,
                const detail::StylePropertySetter<const void *> SET_FUNC,
                const detail::LocalStylePropertySetter<const void *> LOCAL_SET_FUNC,
                const detail::StylePropertyGetter<const void *> GET_FUNC>
        using AnimPath = detail::StyleProperty<const void *, STYLE_PROPERTY, SET_FUNC, LOCAL_SET_FUNC, GET_FUNC>;
#endif

    }

    namespace prop {
        using RADIUS = detail::Integer<LV_STYLE_RADIUS, lv_style_set_radius, lv_obj_set_style_local_radius, lv_obj_get_style_radius>;
        using CLIP_CORNER = detail::Bool<LV_STYLE_CLIP_CORNER, lv_style_set_clip_corner, lv_obj_set_style_local_clip_corner, lv_obj_get_style_clip_corner>;
        using SIZE = detail::Integer<LV_STYLE_SIZE, lv_style_set_size, lv_obj_set_style_local_size, lv_obj_get_style_size>;
        using TRANSFORM_WIDTH = detail::Integer<LV_STYLE_TRANSFORM_WIDTH, lv_style_set_transform_width, lv_obj_set_style_local_transform_width, lv_obj_get_style_transform_width>;
        using TRANSFORM_HEIGHT = detail::Integer<LV_STYLE_TRANSFORM_HEIGHT, lv_style_set_transform_height, lv_obj_set_style_local_transform_height, lv_obj_get_style_transform_height>;
        using TRANSFORM_ANGLE = detail::Integer<LV_STYLE_TRANSFORM_ANGLE, lv_style_set_transform_angle, lv_obj_set_style_local_transform_angle, lv_obj_get_style_transform_angle>;
        using TRANSFORM_ZOOM = detail::Integer<LV_STYLE_TRANSFORM_ZOOM, lv_style_set_transform_zoom, lv_obj_set_style_local_transform_zoom, lv_obj_get_style_transform_zoom>;
        using OPA_SCALE = detail::Opacity<LV_STYLE_OPA_SCALE, lv_style_set_opa_scale, lv_obj_set_style_local_opa_scale, lv_obj_get_style_opa_scale>;

        using PAD_TOP = detail::Integer<LV_STYLE_PAD_TOP, lv_style_set_pad_top, lv_obj_set_style_local_pad_top, lv_obj_get_style_pad_top>;
        using PAD_BOTTOM = detail::Integer<LV_STYLE_PAD_BOTTOM, lv_style_set_pad_bottom, lv_obj_set_style_local_pad_bottom, lv_obj_get_style_pad_bottom>;
        using PAD_LEFT = detail::Integer<LV_STYLE_PAD_LEFT, lv_style_set_pad_left, lv_obj_set_style_local_pad_left, lv_obj_get_style_pad_left>;
        using PAD_RIGHT = detail::Integer<LV_STYLE_PAD_RIGHT, lv_style_set_pad_right, lv_obj_set_style_local_pad_right, lv_obj_get_style_pad_right>;
        using PAD_INNER = detail::Integer<LV_STYLE_PAD_INNER, lv_style_set_pad_inner, lv_obj_set_style_local_pad_inner, lv_obj_get_style_pad_inner>;
        using MARGIN_TOP = detail::Integer<LV_STYLE_MARGIN_TOP, lv_style_set_margin_top, lv_obj_set_style_local_margin_top, lv_obj_get_style_margin_top>;
        using MARGIN_BOTTOM = detail::Integer<LV_STYLE_MARGIN_BOTTOM, lv_style_set_margin_bottom, lv_obj_set_style_local_margin_bottom, lv_obj_get_style_margin_bottom>;
        using MARGIN_LEFT = detail::Integer<LV_STYLE_MARGIN_LEFT, lv_style_set_margin_left, lv_obj_set_style_local_margin_left, lv_obj_get_style_margin_left>;
        using MARGIN_RIGHT = detail::Integer<LV_STYLE_MARGIN_RIGHT, lv_style_set_margin_right, lv_obj_set_style_local_margin_right, lv_obj_get_style_margin_right>;

        using BG_BLEND_MODE = detail::BlendMode<LV_STYLE_BG_BLEND_MODE, lv_style_set_bg_blend_mode, lv_obj_set_style_local_bg_blend_mode, lv_obj_get_style_bg_blend_mode>;
        using BG_MAIN_STOP = detail::Integer<LV_STYLE_BG_MAIN_STOP, lv_style_set_bg_main_stop, lv_obj_set_style_local_bg_main_stop, lv_obj_get_style_bg_main_stop>;
        using BG_GRAD_STOP = detail::Integer<LV_STYLE_BG_GRAD_STOP, lv_style_set_bg_grad_stop, lv_obj_set_style_local_bg_grad_stop, lv_obj_get_style_bg_grad_stop>;
        using BG_GRAD_DIR = detail::GradDir<LV_STYLE_BG_GRAD_DIR, lv_style_set_bg_grad_dir, lv_obj_set_style_local_bg_grad_dir, lv_obj_get_style_bg_grad_dir>;
        using BG_COLOR = detail::Color<LV_STYLE_BG_COLOR, lv_style_set_bg_color, lv_obj_set_style_local_bg_color, lv_obj_get_style_bg_color>;
        using BG_GRAD_COLOR = detail::Color<LV_STYLE_BG_GRAD_COLOR, lv_style_set_bg_grad_color, lv_obj_set_style_local_bg_grad_color, lv_obj_get_style_bg_grad_color>;
        using BG_OPA = detail::Opacity<LV_STYLE_BG_OPA, lv_style_set_bg_opa, lv_obj_set_style_local_bg_opa, lv_obj_get_style_bg_opa>;

        using BORDER_WIDTH = detail::Integer<LV_STYLE_BORDER_WIDTH, lv_style_set_border_width, lv_obj_set_style_local_border_width, lv_obj_get_style_border_width>;
        using BORDER_SIDE = detail::BorderSide<LV_STYLE_BORDER_SIDE, lv_style_set_border_side, lv_obj_set_style_local_border_side, lv_obj_get_style_border_side>;
        using BORDER_BLEND_MODE = detail::BlendMode<LV_STYLE_BORDER_BLEND_MODE, lv_style_set_border_blend_mode, lv_obj_set_style_local_border_blend_mode, lv_obj_get_style_border_blend_mode>;
        using BORDER_POST = detail::Bool<LV_STYLE_BORDER_POST, lv_style_set_border_post, lv_obj_set_style_local_border_post, lv_obj_get_style_border_post>;
        using BORDER_COLOR = detail::Color<LV_STYLE_BORDER_COLOR, lv_style_set_border_color, lv_obj_set_style_local_border_color, lv_obj_get_style_border_color>;
        using BORDER_OPA = detail::Opacity<LV_STYLE_BORDER_OPA, lv_style_set_border_opa, lv_obj_set_style_local_border_opa, lv_obj_get_style_border_opa>;

        using OUTLINE_WIDTH = detail::Integer<LV_STYLE_OUTLINE_WIDTH, lv_style_set_outline_width, lv_obj_set_style_local_outline_width, lv_obj_get_style_outline_width>;
        using OUTLINE_PAD = detail::Integer<LV_STYLE_OUTLINE_PAD, lv_style_set_outline_pad, lv_obj_set_style_local_outline_pad, lv_obj_get_style_outline_pad>;
        using OUTLINE_BLEND_MODE = detail::BlendMode<LV_STYLE_OUTLINE_BLEND_MODE, lv_style_set_outline_blend_mode, lv_obj_set_style_local_outline_blend_mode, lv_obj_get_style_outline_blend_mode>;
        using OUTLINE_COLOR = detail::Color<LV_STYLE_OUTLINE_COLOR, lv_style_set_outline_color, lv_obj_set_style_local_outline_color, lv_obj_get_style_outline_color>;
        using OUTLINE_OPA = detail::Opacity<LV_STYLE_OUTLINE_OPA, lv_style_set_outline_opa, lv_obj_set_style_local_outline_opa, lv_obj_get_style_outline_opa>;

        using SHADOW_WIDTH = detail::Integer<LV_STYLE_SHADOW_WIDTH, lv_style_set_shadow_width, lv_obj_set_style_local_shadow_width, lv_obj_get_style_shadow_width>;
        using SHADOW_OFS_X = detail::Integer<LV_STYLE_SHADOW_OFS_X, lv_style_set_shadow_ofs_x, lv_obj_set_style_local_shadow_ofs_x, lv_obj_get_style_shadow_ofs_x>;
        using SHADOW_OFS_Y = detail::Integer<LV_STYLE_SHADOW_OFS_Y, lv_style_set_shadow_ofs_y, lv_obj_set_style_local_shadow_ofs_y, lv_obj_get_style_shadow_ofs_y>;
        using SHADOW_SPREAD = detail::Integer<LV_STYLE_SHADOW_SPREAD, lv_style_set_shadow_spread, lv_obj_set_style_local_shadow_spread, lv_obj_get_style_shadow_spread>;
        using SHADOW_BLEND_MODE = detail::BlendMode<LV_STYLE_SHADOW_BLEND_MODE, lv_style_set_shadow_blend_mode, lv_obj_set_style_local_shadow_blend_mode, lv_obj_get_style_shadow_blend_mode>;
        using SHADOW_COLOR = detail::Color<LV_STYLE_SHADOW_COLOR, lv_style_set_shadow_color, lv_obj_set_style_local_shadow_color, lv_obj_get_style_shadow_color>;
        using SHADOW_OPA = detail::Opacity<LV_STYLE_SHADOW_OPA, lv_style_set_shadow_opa, lv_obj_set_style_local_shadow_opa, lv_obj_get_style_shadow_opa>;

        using PATTERN_BLEND_MODE = detail::BlendMode<LV_STYLE_PATTERN_BLEND_MODE, lv_style_set_pattern_blend_mode, lv_obj_set_style_local_pattern_blend_mode, lv_obj_get_style_pattern_blend_mode>;
        using PATTERN_REPEAT = detail::Bool<LV_STYLE_PATTERN_REPEAT, lv_style_set_pattern_repeat, lv_obj_set_style_local_pattern_repeat, lv_obj_get_style_pattern_repeat>;
        using PATTERN_RECOLOR = detail::Color<LV_STYLE_PATTERN_RECOLOR, lv_style_set_pattern_recolor, lv_obj_set_style_local_pattern_recolor, lv_obj_get_style_pattern_recolor>;
        using PATTERN_OPA = detail::Opacity<LV_STYLE_PATTERN_OPA, lv_style_set_pattern_opa, lv_obj_set_style_local_pattern_opa, lv_obj_get_style_pattern_opa>;
        using PATTERN_RECOLOR_OPA = detail::Opacity<LV_STYLE_PATTERN_RECOLOR_OPA, lv_style_set_pattern_recolor_opa, lv_obj_set_style_local_pattern_recolor_opa, lv_obj_get_style_pattern_recolor_opa>;
        using PATTERN_IMAGE = detail::Image<LV_STYLE_PATTERN_IMAGE, lv_style_set_pattern_image, lv_obj_set_style_local_pattern_image, lv_obj_get_style_pattern_image>;

        using VALUE_LETTER_SPACE = detail::Integer<LV_STYLE_VALUE_LETTER_SPACE, lv_style_set_value_letter_space, lv_obj_set_style_local_value_letter_space, lv_obj_get_style_value_letter_space>;
        using VALUE_LINE_SPACE = detail::Integer<LV_STYLE_VALUE_LINE_SPACE, lv_style_set_value_line_space, lv_obj_set_style_local_value_line_space, lv_obj_get_style_value_line_space>;
        using VALUE_BLEND_MODE = detail::BlendMode<LV_STYLE_VALUE_BLEND_MODE, lv_style_set_value_blend_mode, lv_obj_set_style_local_value_blend_mode, lv_obj_get_style_value_blend_mode>;
        using VALUE_OFS_X = detail::Integer<LV_STYLE_VALUE_OFS_X, lv_style_set_value_ofs_x, lv_obj_set_style_local_value_ofs_x, lv_obj_get_style_value_ofs_x>;
        using VALUE_OFS_Y = detail::Integer<LV_STYLE_VALUE_OFS_Y, lv_style_set_value_ofs_y, lv_obj_set_style_local_value_ofs_y, lv_obj_get_style_value_ofs_y>;
        using VALUE_ALIGN = detail::Align<LV_STYLE_VALUE_ALIGN, lv_style_set_value_align, lv_obj_set_style_local_value_align, lv_obj_get_style_value_align>;
        using VALUE_COLOR = detail::Color<LV_STYLE_VALUE_COLOR, lv_style_set_value_color, lv_obj_set_style_local_value_color, lv_obj_get_style_value_color>;
        using VALUE_OPA = detail::Opacity<LV_STYLE_VALUE_OPA, lv_style_set_value_opa, lv_obj_set_style_local_value_opa, lv_obj_get_style_value_opa>;
        using VALUE_FONT = detail::Font<LV_STYLE_VALUE_FONT, lv_style_set_value_font, lv_obj_set_style_local_value_font, lv_obj_get_style_value_font>;
        using VALUE_STR = detail::String<LV_STYLE_VALUE_STR, lv_style_set_value_str, lv_obj_set_style_local_value_str, lv_obj_get_style_value_str>;

        using TEXT_LETTER_SPACE = detail::Integer<LV_STYLE_TEXT_LETTER_SPACE, lv_style_set_text_letter_space, lv_obj_set_style_local_text_letter_space, lv_obj_get_style_text_letter_space>;
        using TEXT_LINE_SPACE = detail::Integer<LV_STYLE_TEXT_LINE_SPACE, lv_style_set_text_line_space, lv_obj_set_style_local_text_line_space, lv_obj_get_style_text_line_space>;
        using TEXT_DECOR = detail::TextDecor<LV_STYLE_TEXT_DECOR, lv_style_set_text_decor, lv_obj_set_style_local_text_decor, lv_obj_get_style_text_decor>;
        using TEXT_BLEND_MODE = detail::BlendMode<LV_STYLE_TEXT_BLEND_MODE, lv_style_set_text_blend_mode, lv_obj_set_style_local_text_blend_mode, lv_obj_get_style_text_blend_mode>;
        using TEXT_COLOR = detail::Color<LV_STYLE_TEXT_COLOR, lv_style_set_text_color, lv_obj_set_style_local_text_color, lv_obj_get_style_text_color>;
        using TEXT_SEL_COLOR = detail::Color<LV_STYLE_TEXT_SEL_COLOR, lv_style_set_text_sel_color, lv_obj_set_style_local_text_sel_color, lv_obj_get_style_text_sel_color>;
        using TEXT_OPA = detail::Opacity<LV_STYLE_TEXT_OPA, lv_style_set_text_opa, lv_obj_set_style_local_text_opa, lv_obj_get_style_text_opa>;
        using TEXT_FONT = detail::Font<LV_STYLE_TEXT_FONT, lv_style_set_text_font, lv_obj_set_style_local_text_font, lv_obj_get_style_text_font>;

        using LINE_WIDTH = detail::Integer<LV_STYLE_LINE_WIDTH, lv_style_set_line_width, lv_obj_set_style_local_line_width, lv_obj_get_style_line_width>;
        using LINE_BLEND_MODE = detail::BlendMode<LV_STYLE_LINE_BLEND_MODE, lv_style_set_line_blend_mode, lv_obj_set_style_local_line_blend_mode, lv_obj_get_style_line_blend_mode>;
        using LINE_DASH_WIDTH = detail::Integer<LV_STYLE_LINE_DASH_WIDTH, lv_style_set_line_dash_width, lv_obj_set_style_local_line_dash_width, lv_obj_get_style_line_dash_width>;
        using LINE_DASH_GAP = detail::Integer<LV_STYLE_LINE_DASH_GAP, lv_style_set_line_dash_gap, lv_obj_set_style_local_line_dash_gap, lv_obj_get_style_line_dash_gap>;
        using LINE_ROUNDED = detail::Bool<LV_STYLE_LINE_ROUNDED, lv_style_set_line_rounded, lv_obj_set_style_local_line_rounded, lv_obj_get_style_line_rounded>;
        using LINE_COLOR = detail::Color<LV_STYLE_LINE_COLOR, lv_style_set_line_color, lv_obj_set_style_local_line_color, lv_obj_get_style_line_color>;
        using LINE_OPA = detail::Opacity<LV_STYLE_LINE_OPA, lv_style_set_line_opa, lv_obj_set_style_local_line_opa, lv_obj_get_style_line_opa>;

        using IMAGE_BLEND_MODE = detail::BlendMode<LV_STYLE_IMAGE_BLEND_MODE, lv_style_set_image_blend_mode, lv_obj_set_style_local_image_blend_mode, lv_obj_get_style_image_blend_mode>;
        using IMAGE_RECOLOR = detail::Color<LV_STYLE_IMAGE_RECOLOR, lv_style_set_image_recolor, lv_obj_set_style_local_image_recolor, lv_obj_get_style_image_recolor>;
        using IMAGE_OPA = detail::Opacity<LV_STYLE_IMAGE_OPA, lv_style_set_image_opa, lv_obj_set_style_local_image_opa, lv_obj_get_style_image_opa>;
        using IMAGE_RECOLOR_OPA = detail::Opacity<LV_STYLE_IMAGE_RECOLOR_OPA, lv_style_set_image_recolor_opa, lv_obj_set_style_local_image_recolor_opa, lv_obj_get_style_image_recolor_opa>;

        using TRANSITION_TIME = detail::Integer<LV_STYLE_TRANSITION_TIME, lv_style_set_transition_time, lv_obj_set_style_local_transition_time, lv_obj_get_style_transition_time>;
        using TRANSITION_DELAY = detail::Integer<LV_STYLE_TRANSITION_DELAY, lv_style_set_transition_delay, lv_obj_set_style_local_transition_delay, lv_obj_get_style_transition_delay>;
        using TRANSITION_PROP_1 = detail::Integer<LV_STYLE_TRANSITION_PROP_1, lv_style_set_transition_prop_1, lv_obj_set_style_local_transition_prop_1, lv_obj_get_style_transition_prop_1>;
        using TRANSITION_PROP_2 = detail::Integer<LV_STYLE_TRANSITION_PROP_2, lv_style_set_transition_prop_2, lv_obj_set_style_local_transition_prop_2, lv_obj_get_style_transition_prop_2>;
        using TRANSITION_PROP_3 = detail::Integer<LV_STYLE_TRANSITION_PROP_3, lv_style_set_transition_prop_3, lv_obj_set_style_local_transition_prop_3, lv_obj_get_style_transition_prop_3>;
        using TRANSITION_PROP_4 = detail::Integer<LV_STYLE_TRANSITION_PROP_4, lv_style_set_transition_prop_4, lv_obj_set_style_local_transition_prop_4, lv_obj_get_style_transition_prop_4>;
        using TRANSITION_PROP_5 = detail::Integer<LV_STYLE_TRANSITION_PROP_5, lv_style_set_transition_prop_5, lv_obj_set_style_local_transition_prop_5, lv_obj_get_style_transition_prop_5>;
        using TRANSITION_PROP_6 = detail::Integer<LV_STYLE_TRANSITION_PROP_6, lv_style_set_transition_prop_6, lv_obj_set_style_local_transition_prop_6, lv_obj_get_style_transition_prop_6>;
        using TRANSITION_PATH = detail::AnimPath<LV_STYLE_TRANSITION_PATH, lv_style_set_transition_path, lv_obj_set_style_local_transition_path, lv_obj_get_style_transition_path>;

        using SCALE_WIDTH = detail::Integer<LV_STYLE_SCALE_WIDTH, lv_style_set_scale_width, lv_obj_set_style_local_scale_width, lv_obj_get_style_scale_width>;
        using SCALE_BORDER_WIDTH = detail::Integer<LV_STYLE_SCALE_BORDER_WIDTH, lv_style_set_scale_border_width, lv_obj_set_style_local_scale_border_width, lv_obj_get_style_scale_border_width>;
        using SCALE_END_BORDER_WIDTH = detail::Integer<LV_STYLE_SCALE_END_BORDER_WIDTH, lv_style_set_scale_end_border_width, lv_obj_set_style_local_scale_end_border_width, lv_obj_get_style_scale_end_border_width>;
        using SCALE_END_LINE_WIDTH = detail::Integer<LV_STYLE_SCALE_END_LINE_WIDTH, lv_style_set_scale_end_line_width, lv_obj_set_style_local_scale_end_line_width, lv_obj_get_style_scale_end_line_width>;
        using SCALE_GRAD_COLOR = detail::Color<LV_STYLE_SCALE_GRAD_COLOR, lv_style_set_scale_grad_color, lv_obj_set_style_local_scale_grad_color, lv_obj_get_style_scale_grad_color>;
        using SCALE_END_COLOR = detail::Color<LV_STYLE_SCALE_END_COLOR, lv_style_set_scale_end_color, lv_obj_set_style_local_scale_end_color, lv_obj_get_style_scale_end_color>;

        using PAD_ALL = detail::SettableInteger<lv_style_set_pad_all, lv_obj_set_style_local_pad_all>;
        using PAD_HOR = detail::SettableInteger<lv_style_set_pad_hor, lv_obj_set_style_local_pad_hor>;
        using PAD_VER = detail::SettableInteger<lv_style_set_pad_ver, lv_obj_set_style_local_pad_ver>;
        using MARGIN_ALL = detail::SettableInteger<lv_style_set_margin_all, lv_obj_set_style_local_margin_all>;
        using MARGIN_HOR = detail::SettableInteger<lv_style_set_margin_hor, lv_obj_set_style_local_margin_hor>;
        using MARGIN_VER = detail::SettableInteger<lv_style_set_margin_ver, lv_obj_set_style_local_margin_ver>;

    }


    class Style {
    public:
        Style() {
            lv_style_init(&style_);
        }

        Style(const Style &copy) {
            lv_style_copy(&style_, &copy.style_);
        }

        operator lv_style_t *() {return &style_;};

        template<typename StyleProperty, ObjectState state = ObjectState::DEFAULT>
        Style &style(typename StyleProperty::value_type value) {
            StyleProperty::set_value(&style_, static_cast<lv_state_t>(state), value);
            return *this;
        }

        void reset() {
            lv_style_reset(&style_);
        }

        template<typename StyleProperty, ObjectState state = ObjectState::DEFAULT>
        void remove() {
            lv_style_remove_prop(&style_, StyleProperty::enum_value | (static_cast<lv_state_t>(state) << static_cast<uint8_t>(LV_STYLE_STATE_POS)));
        }

    private:
        lv_style_t style_{};
    };
}
#endif //LVGL_CPP_STYLE_H
