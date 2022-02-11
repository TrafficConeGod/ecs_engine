#include "ecs/entity.hh"
#include "resources/mesh_2d.hh"
#include "components/rigid_transform_2d.hh"
#include "components/rotational_transform_2d.hh"
#include "components/mesh_2d.hh"
#include "lib/vector.hh"
#include "systems/core.hh"
#include "lib/jthread.hh"

using namespace newt;
using namespace ecs;

int main() {
    database db;

    {
        std::scoped_lock lock(db.entity_set.mutex(), db.rigid_transform_2d_set.mutex(), db.mesh_2d_set.mutex());
        auto& e = db.entity_set.at(db.create_entity());
        e.set_component(db, components::rigid_transform_2d{
            .position = {1.f, 1.f},
            .scale = {1.f, 1.618033988749894f}
        });
        auto mesh_resource = std::make_shared<resources::mesh_2d>(std::vector<resources::mesh_2d::triangle>{
            resources::mesh_2d::triangle({
                resources::mesh_2d::vertex{1.f, 1.f},
                resources::mesh_2d::vertex{1.f, 0.f},
                resources::mesh_2d::vertex{0.f, 0.f}
            }),
            resources::mesh_2d::triangle({
                resources::mesh_2d::vertex{0.f, 1.f},
                resources::mesh_2d::vertex{1.f, 1.f},
                resources::mesh_2d::vertex{0.f, 0.f}
            })
        });
        e.set_component(db, components::mesh_2d{
            .resource = mesh_resource
        });
        auto& e2 = db.entity_set.at(db.copy_entity(e));
        e2.get_component<components::rigid_transform_2d>(db) = {
            .position = {0.f, 0.f},
            .scale = {1.f, 1.1f}
        };
    }

    lib::jthread w1(systems::core, &db);

    return 0;
}