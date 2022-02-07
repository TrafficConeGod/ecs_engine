#include "database.hh"
#include "entity.hh"

using namespace newt::ecs;

std::size_t database::create_entity() {
    auto index = entity_set.add(entity(*this));
    entity_set.get_at(index).set_index(index);
    return index;
}