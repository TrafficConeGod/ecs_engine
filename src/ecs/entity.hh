#pragma once
#include "common.hh"
#include "database.hh"
#include <array>
#include <stdexcept>

namespace newt::ecs {
    class entity {
        std::size_t index = 0;
        
        // If the value of a component index is 0 then this entity does not have that component, otherwise the actual index is subtracted by 1
        std::array<std::size_t, MAX_COMPONENTS> component_indices = {0};

        template<typename C>
        const C& get_component_impl(database& db) const {
            if (!has_component<C>()) {
                throw std::runtime_error("no component found");
            }
            // We subtract one since the index stored must be greater than 0
            return db.get_component_set<C>().at(component_indices.at(C::ID) - 1);
        }
        public:
            inline std::size_t get_index() const { return index; }
            inline void set_index(std::size_t index) { this->index = index; }

            // Not inherently thread safe
            template<typename C>
            inline bool has_component() const {
                // If the value is 0, then the component is not present
                return component_indices.at(C::ID) != 0;
            }

            // Not inherently thread safe
            template<typename C>
            inline const C& get_component(database& db) const {
                return get_component_impl<C>(db);
            }

            // Not inherently thread safe
            template<typename C>
            inline C& get_component(database& db) {
                return const_cast<C&>(get_component_impl<C>(db));
            }

            // Not inherently thread safe
            template<typename C>
            void set_component(database& db, const C& component) {
                if (has_component<C>()) {
                    throw std::runtime_error("component already exists");
                }
                // We add one since the index stored must be greater than 0
                component_indices.at(C::ID) = db.get_component_set<C>().insert(component) + 1;
            }

            // Not inherently thread safe
            template<typename C>
            void erase_component(database& db) {
                if (!has_component<C>()) {
                    throw std::runtime_error("no component found");
                }
                // We subtract one since the index stored must be greater than 0
                db.get_component_set<C>().erase_at(component_indices.at(C::ID) - 1);
                // Resetting to the default value
                component_indices.at(C::ID) = 0;
            }
    };
}