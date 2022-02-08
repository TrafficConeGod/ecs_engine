#include "database.hh"
#include "entity.hh"

using namespace newt::ecs;

std::size_t database::create_entity() {
    // We have to assign the index to the entity after it has been created
    auto index = entity_set.insert(entity{});
    entity_set.at(index).set_index(index);
    return index;
}