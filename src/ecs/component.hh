#pragma once
#include <cstddef>
#include "entity.hh"

namespace newt::ecs {
    struct head_component {
        // Getter for the next component ID.
        static std::size_t next_id();
    };

    template<typename R>
    struct base_component : public head_component {
        static const std::size_t ID;
        static const std::size_t SIZE;
    };

    template<typename R>
    struct base_entity_component : public base_component<base_entity_component<R>> {
        entity* entity_ptr;
    };

    template<typename R>
    const std::size_t base_component<R>::ID(head_component::next_id());

    template<typename R>
    const std::size_t base_component<R>::SIZE(sizeof(R));
}