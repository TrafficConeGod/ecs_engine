#pragma once
#include "lib/indexed_set.hh"
#include <mutex>

namespace newt::ecs {
    template<typename T>
    struct database_set {
        std::mutex mutex_;
        lib::indexed_set<T> set;
        public:
            inline std::mutex& mutex() {
                return mutex_;
            }

            inline std::size_t size() const { return set.size(); }

            inline bool has_at(std::size_t index) const {
                return set.has_at(index);
            }

            inline const T& at(std::size_t index) const {
                return set.at(index);
            }

            inline T& at(std::size_t index) {
                return set.at(index);
            }
        
            inline std::size_t insert(const T& value) {
                return set.insert(value);
            }

            inline void erase_at(std::size_t index) {
                set.erase_at(index);
            }

            inline typename lib::indexed_set<T>::iterator begin() {
                return set.begin();
            }

            inline typename lib::indexed_set<T>::iterator end() {
                return set.end();
            }
    };
}