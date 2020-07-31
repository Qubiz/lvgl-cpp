#pragma once

#include "Object.h"

#if LV_USE_TILEVIEW

namespace lvglcpp {

    enum class TileviewPart : uint8_t {
        BG = LV_TILEVIEW_PART_BG,
        SCROLLBAR = LV_TILEVIEW_PART_SCROLLBAR,
        EDGE_FLASH = LV_TILEVIEW_PART_EDGE_FLASH,
    };

    class Tileview final : public Object<Tileview> {
    protected:
        explicit Tileview(lv_obj_t *other) noexcept: Object(other) {};

    public:

        Tileview() noexcept: Object(lv_tileview_create(lv_scr_act(), nullptr)) {};

        explicit Tileview(const Object<> &parent) noexcept
                : Object(lv_tileview_create(parent.get(), nullptr)) {}

        explicit Tileview(const Object<> &parent, const Tileview &copy) noexcept
                : Object(lv_tileview_create(parent.get(), copy.get())) {}

        template<typename Element>
        Tileview &add_element(Element &element) {
            lv_tileview_add_element(get(), element.get());
            return this->underlying();
        }

        /*
         * SETTERS
         */

        Tileview &valid_positions(std::span<lv_point_t> valid_positions) {
            lv_tileview_set_valid_positions(get(), valid_positions.data(), valid_positions.size());
            return this->underlying();
        }

        Tileview &tile_act(lv_coord_t x, lv_coord_t y, lv_anim_enable_t anim) {
            lv_tileview_set_tile_act(get(), x, y, anim);
            return this->underlying();
        }

        Tileview &edge_flash(bool en) {
            lv_tileview_set_edge_flash(get(), en);
            return this->underlying();
        }

        Tileview &anim_time(uint16_t anim_time) {
            lv_tileview_set_anim_time(get(), anim_time);
            return this->underlying();
        }

        /*
         * GETTERS
         */

        std::pair<lv_coord_t, lv_coord_t> tile_act(lv_coord_t *x, lv_coord_t *y) const {
            std::pair<lv_coord_t, lv_coord_t> coords;
            lv_tileview_get_tile_act(get(), &coords.first, &coords.second);
            return coords;
        }

        bool edge_flash() const {
            return lv_tileview_get_edge_flash(get());
        }

        uint16_t anim_time() const {
            return lv_tileview_get_anim_time(get());
        }

    };
}

#endif // LV_USE_TILEVIEW