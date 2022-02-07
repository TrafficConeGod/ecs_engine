#include "ecs/entity.hh"
#include "components/core.hh"
#include <iostream>

using namespace newt;
using namespace ecs;

int main() {
    database db;
    std::size_t entity_index = db.create_entity();

    std::lock_guard lock(db.entity_set.get_mutex());
    auto& e = db.entity_set.get_at(entity_index);

    std::lock_guard lock2(db.core_set.get_mutex());
    e.add_component<components::core>({ .val = 20 });

    // two ways of iterating through components
    for (const auto& c : db.core_set) {
        std::printf("%zu\n", c.val);
    }
    for (const auto& e : db.entity_set) {
        std::printf("%zu\n", e.get_component<components::core>().val);
    }
    return 0;
}