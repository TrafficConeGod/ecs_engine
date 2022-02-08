#include "ecs/entity.hh"
#include "components/core.hh"
#include <iostream>

using namespace newt;
using namespace ecs;

int main() {
    database db;
    auto entity_index = db.create_entity();

    std::scoped_lock lock(db.entity_set.mutex(), db.core_set.mutex());
    auto& e = db.entity_set.at(entity_index);

    e.set_component<components::core>(db, { .val = 20 });
    e.erase_component<components::core>(db);
    e.set_component<components::core>(db, { .val = 20 });

    // two ways of iterating through components
    for (auto& c : db.core_set) {
        std::printf("%zu\n", c.val);
        c.val = 30;
    }
    for (auto& e : db.entity_set) {
        std::printf("%zu\n", e.get_component<components::core>(db).val);
    }

    return 0;
}