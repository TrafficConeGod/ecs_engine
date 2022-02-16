#include "engine/database.hh"

using namespace newt;

#define ERASE_COMPONENT(name) \
if (ent->has_component<components::name>()) { \
    ent->erase_component<components::name>(*this); \
}
#define COPY_COMPONENT(name) \
if (ent.has_component<components::name>()) { \
    copy->set_component(*this, *ent.component<components::name>()); \
}

void engine::database::erase_entity(ecs::entity* ent) {
    NEWT_ENGINE_USE_MACRO_ON_COMPONENTS(ERASE_COMPONENT)
    ecs::database::erase_entity(ent);
}

ecs::entity* engine::database::copy_entity(const ecs::entity& ent) {
    auto copy = ecs::database::copy_entity(ent);
    NEWT_ENGINE_USE_MACRO_ON_COMPONENTS(COPY_COMPONENT)
    return copy;
}