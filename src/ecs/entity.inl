#pragma once
#include "entity.hh"
#include "database.hh"

template<typename C>
void newt::ecs::entity::set_component(database& db, const C& component) {
    auto& component_ptr = get_mutable_component_impl<C>();
    if (component_ptr != nullptr) {
        db.get_component_set<C>().erase(component_ptr);
    }
    auto component_copy = component;
    component_copy.ent = this;
    component_ptr = db.get_component_set<C>().insert(component_copy);
}

template<typename C>
void newt::ecs::entity::erase_component(database& db) {
    auto& component_ptr = get_mutable_component_impl<C>();
    if (component_ptr == nullptr) {
        throw std::runtime_error("no component found");
    }
    component_ptr = nullptr;
    db.get_component_set<C>().erase(component_ptr);
}