#pragma once

#include "Object.h"

namespace lvglcpp {

    class Screen : public Object<Screen> {
    public:
        Screen() : Object(lv_obj_create(nullptr, nullptr)) {};

        void load() {
            lv_scr_load(this->raw());
        }
    };

}
