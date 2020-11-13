#pragma once

#include "Object.h"

#if LV_USE_IMGBTN

#include "Button.h"

namespace lvglcpp {

    enum class ImageButtonPart : lv_imgbtn_part_t {
        MAIN = LV_IMGBTN_PART_MAIN
    };

    class ImageButton : public Object<ImageButton> {
    protected:
        explicit ImageButton(lv_obj_t *other) noexcept: Object(other) {};

    public:

        ImageButton() noexcept: Object(lv_imgbtn_create(lv_scr_act(), nullptr)) {};

        template<typename T>
        explicit ImageButton(const Object<T> &parent) noexcept
                : Object(lv_imgbtn_create(parent.raw(), nullptr)) {}

        template<typename T>
        explicit ImageButton(const Object<T> &parent, const ImageButton &copy) noexcept
                : Object(lv_imgbtn_create(parent.raw(), copy.raw())) {}

        /*
         * SETTERS
         */

        ImageButton &src(lv_obj_t *imgbtn, lv_btn_state_t state, const void *src) {
            lv_imgbtn_set_src(raw(), state, src);
            return this->underlying();
        }

        ImageButton &checkable(lv_obj_t *imgbtn, bool tgl) {
            lv_imgbtn_set_checkable(raw(), tgl);
            return this->underlying();
        }

        ImageButton &state(lv_obj_t *imgbtn, lv_btn_state_t state) {
            lv_imgbtn_set_state(raw(), state);
            return this->underlying();
        }

        ImageButton &toggle(lv_obj_t *imgbtn) {
            lv_imgbtn_toggle(raw());
            return this->underlying();
        }

#if LV_IMGBTN_TILED
        ImageButton & src_tiled(ButtonState state, const void * src_left, const void * src_mid,
                             const void * src_right) {
            lv_imgbtn_set_src_tiled(get(), static_cast<lv_btn_state_t(state), src_left, src_mid, src_right);
            return this->underlying();
        }
#endif

        /*
         * GETTERS
         */

        [[nodiscard]] const void *src(ButtonState state) const {
            return lv_imgbtn_get_src(raw(), static_cast<lv_btn_state_t>(state));
        }

        [[nodiscard]] ButtonState state() const {
            return static_cast<ButtonState>(lv_imgbtn_get_state(raw()));
        }

        [[nodiscard]] bool checkable() const {
            return lv_imgbtn_get_checkable(raw());
        }

    };
}

#endif // LV_USE_IMGBTN