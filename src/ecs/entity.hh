#pragma once
#include "components_def.hh"
#include "common.hh"
#include <array>
#include <stdexcept>

#define MAKE_COMPONENT_POINTER(name) components::name* name##_ptr = nullptr;

namespace newt::ecs {
    struct database;

    class entity {
        USE_MACRO_ON_COMPONENTS(MAKE_COMPONENT_POINTER)

        template<typename C>
        const C*& get_component_impl() const;

        template<typename C>
        inline C*& get_mutable_component_impl() {
            return const_cast<C*&>(get_component_impl<C>());
        }
        public:
            entity() = default;
            entity(const entity&) = delete;
            entity& operator=(const entity&) = delete;
        
            // Not inherently thread safe
            template<typename C>
            inline bool has_component() const {
                return get_component_impl<C>() != nullptr;
            }

            // Not inherently thread safe
            template<typename C>
            inline const C* get_component() const {
                auto& component_ptr = get_mutable_component_impl<C>();
                if (component_ptr != nullptr) {
                    throw std::runtime_error("no component found");
                }
                return get_component_impl<C>();
            }

            // Not inherently thread safe
            template<typename C>
            inline C* get_component() {
                auto& component_ptr = get_mutable_component_impl<C>();
                if (component_ptr != nullptr) {
                    throw std::runtime_error("no component found");
                }
                return get_mutable_component_impl<C>();
            }

            // Not inherently thread safe
            template<typename C>
            void set_component(database& db, const C& component);

            // Not inherently thread safe
            template<typename C>
            void erase_component(database& db);
    };
}