#pragma once
#include "ecs/component.hh"
#include "lib/vector.hh"

namespace newt::components {
    struct rotational_transform_2d : public ecs::base_component<rotational_transform_2d> {
        lib::vector<float, 2> forward;
    };
}