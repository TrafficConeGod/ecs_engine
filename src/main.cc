#include "ecs/entity.hh"
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
    db.add_component_type<components::rigid_transform_2d>();
    db.add_component_type<components::rotational_transform_2d>();
    db.add_component_type<components::mesh_2d>();

    {
        std::scoped_lock lock(db.entities().mutex(), db.components<components::rigid_transform_2d>().mutex(), db.components<components::mesh_2d>().mutex());
        auto& ent = *db.create_entity();
        ent.set_component(db, components::rigid_transform_2d{
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
        ent.set_component(db, components::mesh_2d{
            .resource = mesh_resource
        });
    }

    lib::jthread w1(systems::core, &db);

    return 0;
}