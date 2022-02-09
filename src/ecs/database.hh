#pragma once
#include "database_set.hh"

namespace newt::components {
    struct rigid_transform_2d;
    struct rotational_transform_2d;
    struct mesh_2d;
};

#define MAKE_COMPONENT_SET(name) database_set<components::name> name##_set;

#define MAKE_COMPONENT_TEMPLATE_ACCESS(name) \
template<> \
constexpr const database_set<components::name>& get_component_set<components::name>(const database& db) { \
    return db.name##_set; \
} \

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
        MAKE_COMPONENT_SET(rigid_transform_2d)
        MAKE_COMPONENT_SET(rotational_transform_2d)
        MAKE_COMPONENT_SET(mesh_2d)

        database() = default;
        database(const database&) = delete;
        database(database&&) = delete;
        database& operator=(const database&) = delete;

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
        MAKE_COMPONENT_TEMPLATE_ACCESS(rigid_transform_2d)
        MAKE_COMPONENT_TEMPLATE_ACCESS(rotational_transform_2d)
        MAKE_COMPONENT_TEMPLATE_ACCESS(mesh_2d)
    }
}