#include "entity.hh"

template<typename C>
void newt::ecs::entity::set_component(database& db, const C& component) {
    if (has_component<C>()) {
        db.components<C>().erase(mutable_component_impl<C>());
        components.erase_at(C::ID);
    }
    auto component_copy = component;
    component_copy.entity_ptr = this;
    auto component_ptr = db.components<C>().insert(component_copy);
    components.insert(C::ID, component_ptr);
}

template<typename C>
void newt::ecs::entity::erase_component(database& db) {
    if (!has_component<C>()) {
        throw std::runtime_error("no component found");
    }
    db.components<C>().erase(mutable_component_impl<C>());
    components.erase_at(C::ID);
}