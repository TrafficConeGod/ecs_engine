#include "database.hh"
#include "entity.hh"
#include "components/rigid_transform_2d.hh"
#include "components/rotational_transform_2d.hh"
#include "components/mesh_2d.hh"

using namespace newt;
using namespace ecs;

#define MAKE_COMPONENT_COPY(name) \
if (ent.has_component<components::name>()) { \
    clone.set_component<components::name>(*this, ent.get_component<components::name>(*this)); \
} \

std::size_t database::create_entity() {
    // We have to assign the index to the entity after it has been created
    auto index = entity_set.insert({});
    entity_set.at(index).set_index(index);
    return index;
}

std::size_t database::copy_entity(const entity& ent) {
    auto& clone = entity_set.at(create_entity());
    MAKE_COMPONENT_COPY(rigid_transform_2d)
    MAKE_COMPONENT_COPY(rotational_transform_2d)
    MAKE_COMPONENT_COPY(mesh_2d)
    return clone.get_index();
}