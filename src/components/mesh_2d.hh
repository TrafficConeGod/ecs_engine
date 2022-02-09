#pragma once
#include "ecs/component.hh"
#include "resources/mesh_2d.hh"
#include <memory>

namespace newt::components {
    struct mesh_2d : public ecs::base_entity_component<mesh_2d> {
        std::shared_ptr<resources::mesh_2d> resource;
    };
}