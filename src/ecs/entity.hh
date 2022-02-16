#pragma once
#include <array>
#include <stdexcept>
#include "lib/index_map.hh"
#include "database_colony.hh"
#include <memory>
#include "lib/any_ptr.hh"
namespace newt::ecs {
    class entity {
        lib::index_map<lib::any_ptr> components;

        template<typename C>
        inline const C* component_impl() const {
            return components.at(C::ID).template get<C>();
        }

        template<typename C>
        inline C* mutable_component_impl() {
            return components.at(C::ID).template get<C>();
        }
        public:
            entity() = default;
            // entity(const entity&) = delete;
            // entity& operator=(const entity&) = delete;

            // Not inherently thread safe
            template<typename C>
            inline bool has_component() const {
                return components.has_at(C::ID);
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
                if (!has_component<C>()) {
                    throw std::runtime_error("no component found");
                }
                return mutable_component_impl<C>();
            }

            // Not inherently thread safe
            template<typename C, typename D>
            void set_component(D& db, const C& component) {
                if (has_component<C>()) {
                    db.template components<C>().erase(mutable_component_impl<C>());
                    components.erase_at(C::ID);
                }
                auto component_copy = component;
                component_copy.entity_ptr = this;
                auto component_ptr = db.template components<C>().insert(component_copy);
                components.insert_at(C::ID, component_ptr);
            }

            // Not inherently thread safe
            template<typename C, typename D>
            void erase_component(D& db) {
                if (!has_component<C>()) {
                    throw std::runtime_error("no component found");
                }
                db.template components<C>().erase(mutable_component_impl<C>());
                components.erase_at(C::ID);
            }
    };
}