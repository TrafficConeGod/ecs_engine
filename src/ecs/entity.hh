#pragma once
#include <array>
#include <stdexcept>
#include "lib/index_map.hh"
#include "database_colony.hh"
#include <memory>
#include <any>

namespace newt::ecs {
    class database;

    class entity {
        lib::index_map<std::any> components;

        template<typename C>
        inline const C* component_impl() const {
            return std::any_cast<const C*>(components.at(C::ID));
        }

        template<typename C>
        inline C* mutable_component_impl() {
            return std::any_cast<C*>(components.at(C::ID));
        }
        public:
            entity() = default;
            // entity(const entity&) = delete;
            // entity& operator=(const entity&) = delete;
        
            // Not inherently thread safe
            template<typename C>
            inline bool has_component() const {
                return components.has_at(C::ID) && component_impl<C>() != nullptr;
            }

            // Not inherently thread safe
            template<typename C>
            inline const C* component() const {
                if (!has_component<C>()) {
                    throw std::runtime_error("no component found");
                }
                return component_impl<C>();
            }

            // Not inherently thread safe
            template<typename C>
            inline C* component() {
                return const_cast<C*>(component<C>());
            }

            // Not inherently thread safe
            template<typename C>
            void set_component(database& db, const C& component);

            // Not inherently thread safe
            template<typename C>
            void erase_component(database& db);
    };
}