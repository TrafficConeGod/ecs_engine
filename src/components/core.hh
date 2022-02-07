#pragma once
#include "ecs/component.hh"

namespace newt::components {
    struct core : public ecs::base_component<core> {
        std::size_t val = 0;
    };
}