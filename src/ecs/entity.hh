#pragma once
#include "common.hh"
#include "database.hh"
#include <array>
#include <stdexcept>

namespace newt::ecs {
    class entity {
        database& db;
        std::size_t index = 0;
        
        std::array<std::size_t, MAX_COMPONENTS> component_indices = {0};
        public:
            inline entity(database& db_) : db(db_) {}

            inline std::size_t get_index() const { return index; }
            inline void set_index(std::size_t index) { this->index = index; }

            template<typename C>
            inline bool has_component() const {
                return component_indices.at(C::ID) != 0;
            }

            template<typename C>
            inline const C& get_component() const {
                if (!has_component<C>()) {
                    throw std::runtime_error("no component found");
                }
                return db.get_component_set<C>().get_at(component_indices.at(C::ID) - 1);
            }

            template<typename C>
            void add_component(const C& component) {
                if (has_component<C>()) {
                    throw std::runtime_error("component already exists");
                }
                component_indices.at(C::ID) = db.get_component_set<C>().add(component) + 1;
            }

            template<typename C>
            void remove_component() {
                if (!has_component<C>()) {
                    throw std::runtime_error("no component found");
                }
                db.get_component_set<C>().remove_at(component_indices.at(C::ID) - 1);
                component_indices.at(C::ID) = 0;
            }
    };
}