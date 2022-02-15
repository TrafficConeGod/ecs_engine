#pragma once
#include "lib/index_map.hh"
#include "database_colony.hh"
#include "entity.hh"
#include <memory>
#include <any>

namespace newt::ecs {
    class database;

    class database {
        database_colony<entity> entities_;
        lib::index_map<std::unique_ptr<std::any>> component_colonies;

        template<typename C>
        inline const database_colony<C>& components_impl() const {
            return std::any_cast<const database_colony<C>&>(*component_colonies.at(C::ID));
        }

        public:
            database() = default;
            database(const database&) = delete;
            database& operator=(const database&) = delete;

            template<typename C>
            inline void add_component_type() {
                component_colonies.insert(C::ID, std::make_unique<std::any>(database_colony<C>()));
            }

            inline const database_colony<entity>& entities() const { return entities_; }
            inline database_colony<entity>& entities() { return entities_; }
            inline entity* create_entity() {
                return &(*entities_.insert({}));
            }
            entity* copy_entity(const entity* ent);

            template<typename C>
            inline const database_colony<C>& components() const { return components_impl<C>(); }
            template<typename C>
            inline database_colony<C>& components() { return const_cast<database_colony<C>&>(components_impl<C>()); }
    };
}

#include "entity.inl"