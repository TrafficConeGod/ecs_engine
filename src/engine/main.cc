#include "ecs/entity.hh"
#include "components/core.hh"
#include "lib/vector.hh"
#include <iostream>

using namespace newt;
using namespace ecs;

int main() {
    database db;
    auto entity_index = db.create_entity();

    std::scoped_lock lock(db.entity_set.mutex(), db.core_set.mutex());
    db.core_set.listening_for_inserted_indices() = true;
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

    for (auto& index : db.core_set.move_inserted_indices()) {
        std::printf("%zu\n", index);
    }

    lib::vector<float, 3> vec = {2, 3, 4};
    vec *= 20.3f;
    vec.print();

    lib::vector<int, 3> v2 = vec;
    v2.print();

    return 0;
}