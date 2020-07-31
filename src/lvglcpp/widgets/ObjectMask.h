#pragma once

#include "Object.h"

#if LV_USE_OBJMASK

namespace lvglcpp {

    enum class ObjectMaskPart : lv_objmask_part_t {
        MAIN = LV_OBJMASK_PART_MAIN,
    };


    class ObjectMask final : public Object<ObjectMask> {
    protected:
        explicit ObjectMask(lv_obj_t *other) noexcept: Object(other) {};

    public:

        ObjectMask() noexcept: Object(lv_objmask_create(lv_scr_act(), nullptr)) {};

        explicit ObjectMask(const Object<> &parent) noexcept
                : Object(lv_objmask_create(parent.get(), nullptr)) {}

        explicit ObjectMask(const Object<> &parent, const ObjectMask &copy) noexcept
                : Object(lv_objmask_create(parent.get(), copy.get())) {}

        lv_objmask_mask_t *add(void *params) {
            return lv_objmask_add_mask(get(), params);
        }

        ObjectMask &update(lv_objmask_mask_t *mask, void *param) {
            lv_objmask_update_mask(get(), mask, param);
            return this->underlying();
        }

        ObjectMask &remove(lv_objmask_mask_t *mask, void *param) {
            lv_objmask_update_mask(get(), mask, param);
            return this->underlying();
        }

    };
}

#endif // LV_USE_OBJMASK