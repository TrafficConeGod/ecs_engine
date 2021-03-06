#pragma once
#include <vector>
#include <list>
#include <stdexcept>

namespace newt::lib {
    template<typename T>
    class index_map {
        // Container for the actual data since this set may contain elements with no value.
        struct value_container {
            bool has_value = false;
            T value;
        };

        std::vector<value_container> containers;
        std::list<std::size_t> free_indices;

        const T& at_impl(const std::size_t index) const {
            auto& container = containers.at(index);
            if (!container.has_value) {
                throw std::out_of_range("value not found");
            }
            return container.value;
        }
        public:
            inline std::size_t size() const { return containers.size(); }

            inline bool has_at(const std::size_t index) const {
                // Make sure we are not out of bounds and that the value exists
                return index < containers.size() && containers.at(index).has_value;
            }

            inline const T& at(const std::size_t index) const {
                return at_impl(index);
            }

            inline T& at(const std::size_t index) {
                return const_cast<T&>(at_impl(index));
            }
            
            void insert_at(const std::size_t index, T&& value) {
                // If we don't have an index, get one
                if (index >= containers.size()) {
                    // Add the in between indices to the free indices
                    for (std::size_t i = containers.size(); i < index; i++) {
                        free_indices.push_back(i);
                    }

                    // Resize and insert the value
                    containers.resize(index + 1);
                    auto& container = containers.at(index);
                    container = { .has_value = true, .value = std::move(value) };
                } else {
                    auto& container = containers.at(index);
                    if (container.has_value) {
                        throw std::runtime_error("value already exists");
                    }
                    container = { .has_value = true, .value = std::move(value) };
                }
            }
        
            std::size_t insert(T&& value) {
                // If we have a free index, use one of them
                if (free_indices.size() > 0) {
                    for (;;) {
                        auto index = free_indices.back();
                        free_indices.pop_back();
                        auto& container = containers.at(index);
                        // Since not all free indices are actually free we need to check if the container is empty (this is because of insert_at)
                        if (container.has_value) {
                            continue;
                        }
                        container = { .has_value = true, .value = std::move(value) };
                        return index;
                    }
                } else {
                    auto index = containers.size();
                    containers.push_back({ .has_value = true, .value = std::move(value) });
                    return index;
                }
            }

            void erase_at(const std::size_t index) {
                auto& container = containers.at(index);
                // if (container.has_value) {
                //     auto moved = std::move(container);
                // }
                container.has_value = false;
                // Add a new free index
                free_indices.push_back(index);
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

            inline iterator begin() {
                auto it = containers.begin();
                auto end = containers.end();
                // If there is no value at the current location, then we need to increment until we find one
                while (it != end && !it->has_value) {
                    it++;
                }
                return iterator(it, end);
            }

            inline iterator end() {
                return iterator(containers.end(), containers.end());
            }

            class const_iterator {
                private:
                    typename std::vector<value_container>::const_iterator it;
                    typename std::vector<value_container>::const_iterator end;
                public:
                    inline const_iterator(const typename std::vector<value_container>::const_iterator& it_, const typename std::vector<value_container>::const_iterator& end_) : it(it_), end(end_) {}

                    inline const_iterator& operator++() {
                        it++;
                        // If there is no value at the current location, then we need to increment until we find one
                        while (it != end && !it->has_value) {
                            it++;
                        }
                        return *this;
                    }

                    inline bool operator!=(const const_iterator& rhs) const {
                        return it != rhs.it;
                    }

                    inline const T& operator*() {
                        return it->value;
                    }
            };

            inline const_iterator begin() const {
                auto it = containers.begin();
                auto end = containers.end();
                // If there is no value at the current location, then we need to increment until we find one
                while (it != end && !it->has_value) {
                    it++;
                }
                return const_iterator(it, end);
            }

            inline const_iterator end() const {
                return const_iterator(containers.end(), containers.end());
            }
    };
}