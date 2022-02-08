#pragma once
#include "database_set.hh"

namespace newt::components {
    struct core;
};

namespace newt::ecs {
    struct entity;
    struct database;

    // C++ template magic to get the component set from type
    namespace database_impl {
        template<typename C>
        constexpr const database_set<C>& get_component_set(const database& db);
    }

    struct database {
        database_set<entity> entity_set;
        database_set<components::core> core_set;

        std::size_t create_entity();

        template<typename C>
        constexpr const database_set<C>& get_component_set() const {
            return database_impl::get_component_set<C>(*this);
        }
        template<typename C>
        constexpr database_set<C>& get_component_set() {
            return const_cast<database_set<C>&>(database_impl::get_component_set<C>(*this));
        }
    };

    // Implementation of get_component_set
    namespace database_impl {
        template<>
        constexpr const database_set<components::core>& get_component_set<components::core>(const database& db) {
            return db.core_set;
        }
    }
}