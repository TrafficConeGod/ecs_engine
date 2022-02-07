#pragma once
#include <mutex>
#include <vector>
#include <stdexcept>

namespace newt::ecs {
    template<typename T>
    class indexed_set {
        std::mutex mutex;

        // Container for the actual data since this set may contain elements with no value.
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
            // IMPORTANT: Always lock the mutex of this indexed set *before* using any of the non inherently thread safe functions
            inline std::mutex& get_mutex() {
                return mutex;
            }
    
            inline std::size_t get_size() const { return containers.size(); }
        
            // Not inherently thread safe
            std::size_t add(const T& value) {
                std::size_t index = containers.size();
                containers.push_back({ .has_value = true, .value = value });
                return index;
            }

            // Not inherently thread safe
            void remove_at(std::size_t index) {
                containers.at(index).has_value = false;
            }

            // Not inherently thread safe
            bool has_at(std::size_t index) const {
                return containers.at(index).has_value;
            }

            // Not inherently thread safe
            inline const T& get_at(std::size_t index) const {
                return get_at_impl(index);
            }

            // Not inherently thread safe
            inline T& get_at(std::size_t index) {
                return const_cast<T&>(get_at_impl(index));
            }

            class iterator {
                private:
                    typename std::vector<value_container>::iterator it;
                    typename std::vector<value_container>::iterator end;
                public:
                    inline iterator(const typename std::vector<value_container>::iterator& it_, const typename std::vector<value_container>::iterator& end_) : it(it_), end(end_) {}

                    inline iterator& operator++() {
                        it++;
                        // If there is no value at the current location, then we need to increment until we find one
                        while (it != end && !it->has_value) {
                            it++;
                        }
                        return *this;
                    }

                    inline bool operator!=(const iterator& rhs) const {
                        return it != rhs.it;
                    }

                    inline T& operator*() {
                        return it->value;
                    }
            };

            // Not inherently thread safe
            inline iterator begin() {
                return iterator(containers.begin(), containers.end());
            }

            // Not inherently thread safe
            inline iterator end() {
                return iterator(containers.end(), containers.end());
            }
    };
}