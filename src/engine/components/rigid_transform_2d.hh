#pragma once
#include "ecs/component.hh"
#include "lib/vector.hh"

namespace newt::engine::components {
    struct rigid_transform_2d : public ecs::base_entity_component<rigid_transform_2d> {
        lib::vector<float, 2> position;
        lib::vector<float, 2> scale;
    };
}