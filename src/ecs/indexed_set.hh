#pragma once
#include <mutex>
#include <vector>
#include <stdexcept>

namespace newt::ecs {
    template<typename T>
    class indexed_set {
        std::mutex mutex;

        struct value_container {
            bool has_value = true;
            T value;
        };

        std::vector<value_container> containers;

        const T& get_at_impl(std::size_t index) const {
            auto& container = containers.at(index);
            if (!container.has_value) {
                throw std::out_of_range("value not found");
            }
            return container.value;
        }
        public:
            inline std::mutex& get_mutex() {
                return mutex;
            }

            inline std::size_t get_size() const { return containers.size(); }
        
            std::size_t add(const T& value) {
                std::size_t index = containers.size();
                containers.push_back({ .has_value = true, .value = value });
                return index;
            }

            void remove_at(std::size_t index) {
                containers.at(index).has_value = false;
            }

            bool has_at(std::size_t index) const {
                return containers.at(index).has_value;
            }

            inline const T& get_at(std::size_t index) const {
                return get_at_impl(index);
            }

            inline T& get_at(std::size_t index) {
                return const_cast<T&>(get_at_impl(index));
            }

            class iterator {
                private:
                    indexed_set& ref;
                    std::size_t index;
                public:
                    inline iterator(indexed_set& ref_, std::size_t index_) : ref(ref_), index(index_) {}

                    inline iterator& operator++() {
                        index++;
                        while (index < ref.get_size() && !ref.has_at(index)) {
                            index++;
                        }
                        return *this;
                    }

                    inline bool operator!=(const iterator& it) const {
                        return index != it.index;
                    }

                    inline T& operator*() {
                        return ref.get_at(index);
                    }
            };

            inline iterator begin() {
                return iterator(*this, 0);
            }

            inline iterator end() {
                return iterator(*this, containers.size());
            }
    };
}