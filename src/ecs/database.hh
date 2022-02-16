#pragma once
#include "lib/index_map.hh"
#include "database_colony.hh"
#include "entity.hh"
#include <memory>
#include <any>

#define MAKE_COMPONENT_COLONY(name) newt::ecs::database_colony<components::name> name##_colony;

namespace newt::ecs {
    class database;

    class database {
        database_colony<entity> entities_;
        protected:
            template<typename C>
            const database_colony<C>& components_impl() const;
        public:
            database() = default;
            database(const database&) = delete;
            database& operator=(const database&) = delete;

            inline const database_colony<entity>& entities() const { return entities_; }
            inline database_colony<entity>& entities() { return entities_; }
            inline entity* create_entity() {
                return &(*entities_.insert({}));
            }
            inline void destroy_entity(entity* ent) {
                entities_.erase(ent);
            }
            inline entity* copy_entity(const entity& ent) {
                return create_entity();
            }

            template<typename C>
            constexpr const database_colony<C>& components() const { return components_impl<C>(); }
            template<typename C>
            constexpr database_colony<C>& components() { return const_cast<database_colony<C>&>(components_impl<C>()); }
    };
}