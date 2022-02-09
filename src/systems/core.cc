#include "core.hh"
#include "routines/render.hh"
#include <mutex>

using namespace newt;
using namespace ecs;

void systems::core(database* db_ptr) {
    auto& db = *db_ptr;

    for (;;) {
        std::scoped_lock lock(db.entity_set.mutex());
        {
            std::scoped_lock lock2(db.rigid_transform_2d_set.mutex(), db.rotational_transform_2d_set.mutex(), db.mesh_2d_set.mutex());
            systems::routines::render(db);
        }
    }
}