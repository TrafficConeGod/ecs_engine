#include "ecs/entity.hh"
#include "components/rigid_transform_2d.hh"
#include "components/rotational_transform_2d..hh"
#include "lib/vector.hh"
#include "systems/core.hh"
#include "lib/jthread.hh"

using namespace newt;
using namespace ecs;
using namespace components;

int main() {
    database db;

    std::scoped_lock lock(db.entity_set.mutex(), db.rigid_transform_2d_set.mutex());
    auto& e = db.entity_set.at(db.create_entity());
    e.set_component<rigid_transform_2d>(db, {
        .position = {1.f, 2.f},
        .scale = {1.f, 1.618033988749894f}
    });

    lib::jthread w1(systems::core, &db);

    return 0;
}