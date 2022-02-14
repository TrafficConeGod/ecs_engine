#pragma once
#include "components_def.hh"
#include "database_set.hh"
#include "entity.hh"

#define MAKE_COMPONENT_SET(name) database_set<components::name> name##_set;

#define MAKE_COMPONENT_TEMPLATE_ACCESS(name) \
template<> \
constexpr const database_set<components::name>& get_component_set<components::name>(const database& db) { \
    return db.name##_set; \
} \

namespace newt::ecs {
    struct database;

    struct database {
        database_set<entity> entity_set;
        USE_MACRO_ON_COMPONENTS(MAKE_COMPONENT_SET)

        database() = default;
        database(const database&) = delete;
        database& operator=(const database&) = delete;

        entity* copy_entity(const entity* ent);

        template<typename C>
        constexpr const database_set<C>& get_component_set() const {
            return get_component_set_impl<C>();
        }
        template<typename C>
        constexpr database_set<C>& get_component_set() {
            return const_cast<database_set<C>&>(get_component_set_impl<C>());
        }
        private:
            template<typename C>
            constexpr const database_set<C>& get_component_set_impl() const;
    };
}