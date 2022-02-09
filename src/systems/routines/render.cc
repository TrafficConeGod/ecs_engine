#include "render.hh"
#include "ecs/entity.hh"
#include "components/mesh_2d.hh"
#include "components/rigid_transform_2d.hh"
#include <cstdio>

using namespace newt;
using namespace ecs;

void systems::routines::render(database& db) {
    for (auto& mesh : db.mesh_2d_set) {
        auto& entity = db.entity_set.at(mesh.entity_index);
        if (entity.has_component<components::rigid_transform_2d>()) {
            auto& rtf = entity.get_component<components::rigid_transform_2d>(db);
            std::printf("position = "); rtf.position.print(); std::printf(";\n");
            std::printf("scale = "); rtf.scale.print(); std::printf(";\n");
        }
    }
}