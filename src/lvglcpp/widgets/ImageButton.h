#pragma once

#include "Object.h"

#if LV_USE_IMGBTN

#include "Button.h"

namespace lvglcpp {

    enum class ImageButtonPart : lv_imgbtn_part_t {
        MAIN = LV_IMGBTN_PART_MAIN
    };

    class ImageButton final : public Object<ImageButton> {
    protected:
        explicit ImageButton(lv_obj_t *other) noexcept: Object(other) {};

    public:

        ImageButton() noexcept: Object(lv_imgbtn_create(lv_scr_act(), nullptr)) {};

        explicit ImageButton(const Object<> &parent) noexcept
                : Object(lv_imgbtn_create(parent.get(), nullptr)) {}

        explicit ImageButton(const Object<> &parent, const ImageButton &copy) noexcept
                : Object(lv_imgbtn_create(parent.get(), copy.get())) {}

        /*
         * SETTERS
         */

        ImageButton &src(lv_obj_t *imgbtn, lv_btn_state_t state, const void *src) {
            lv_imgbtn_set_src(get(), state, src);
            return this->underlying();
        }

        ImageButton &checkable(lv_obj_t *imgbtn, bool tgl) {
            lv_imgbtn_set_checkable(get(), tgl);
            return this->underlying();
        }

        ImageButton &state(lv_obj_t *imgbtn, lv_btn_state_t state) {
            lv_imgbtn_set_state(get(), state);
            return this->underlying();
        }

        ImageButton &toggle(lv_obj_t *imgbtn) {
            lv_imgbtn_toggle(get());
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

        [[nodiscard]] const void * src(ButtonState state) const {
            return lv_imgbtn_get_src(get(), static_cast<lv_btn_state_t>(state));
        }
        [[nodiscard]] ButtonState state() const {
            return static_cast<ButtonState>(lv_imgbtn_get_state(get()));
        }
        [[nodiscard]] bool checkable() const {
            return lv_imgbtn_get_checkable(get());
        }

    };
}

#endif // LV_USE_IMGBTN