#pragma once
#include "ecs/component.hh"
#include "engine/resources/shader.hh"
#include <memory>

namespace newt::engine::components {
    struct shader : public ecs::base_entity_component<shader> {
        std::shared_ptr<resources::shader> resource;
    };
}