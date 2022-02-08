#pragma once
#include "lib/indexed_set.hh"
#include <mutex>

namespace newt::ecs {
    template<typename T>
    struct database_set : public lib::indexed_set<T> {
        std::mutex mutex;
    };
}