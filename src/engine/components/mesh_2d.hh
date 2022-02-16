#pragma once
#include "ecs/component.hh"
#include "engine/resources/mesh_2d.hh"
#include <memory>

namespace newt::engine::components {
    struct mesh_2d : public ecs::base_entity_component<mesh_2d> {
        std::shared_ptr<resources::mesh_2d> resource;
    };
}