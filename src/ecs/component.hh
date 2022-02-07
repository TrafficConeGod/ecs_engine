#pragma once
#include <cstddef>

namespace newt::ecs {
    struct head_component {
        static std::size_t next_id();
    };

    template<typename R>
    struct base_component : public head_component {
        static const std::size_t ID;
        static const std::size_t SIZE;
    };

    template<typename R>
    const std::size_t base_component<R>::ID(head_component::next_id());

    template<typename R>
    const std::size_t base_component<R>::SIZE(sizeof(R));
}