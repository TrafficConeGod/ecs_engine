#pragma once
#include "lib/indexed_set.hh"
#include <mutex>
#include <stdexcept>

namespace newt::ecs {
    template<typename T>
    struct database_set {
        std::mutex mutex_;
        lib::indexed_set<T> set;
        bool listening_for_inserted_indices_ = false;
        std::vector<std::size_t> inserted_indices;
        public:
            inline std::mutex& mutex() {
                return mutex_;
            }

            // Whether or not to listen for insertion and add the indices to the inserted_indices vector
            inline bool& listening_for_inserted_indices() {
                return listening_for_inserted_indices_;
            }

            inline std::size_t size() const { return set.size(); }

            inline bool has_at(std::size_t index) const {
                return set.has_at(index);
            }

            inline const T& at(std::size_t index) const {
                return set.at(index);
            }

            T& at(std::size_t index) {
                return set.at(index);
            }
        
            std::size_t insert(const T& value) {
                // If we are listening for inserted indices, add the index to the inserted_indices vector
                if (listening_for_inserted_indices_) {
                    inserted_indices.push_back(set.insert(value));
                    return inserted_indices.back();
                } else {
                    return set.insert(value);
                }
            }

            void erase_at(std::size_t index) {
                // If we are listening for inserted indices, remove the index from the inserted_indices vector
                if (listening_for_inserted_indices_) {
                    // Since std::erase_if would be less efficient, we have to do it manually
                    for (auto it = inserted_indices.begin(); it != inserted_indices.end(); ++it) {
                        if (*it == index) {
                            inserted_indices.erase(it);
                            break;
                        }
                    }
                }
                set.erase_at(index);
            }

            void clear_inserted_indices() {
                inserted_indices.clear();
            }

            std::vector<std::size_t> copy_inserted_indices() const {
                if (!listening_for_inserted_indices_) {
                    throw std::runtime_error("listening_for_inserted_indices must be true to use this function");
                }
                return inserted_indices;
            }

            inline auto begin() {
                return set.begin();
            }

            inline auto end() {
                return set.end();
            }

            inline auto begin() const {
                return set.begin();
            }

            inline auto end() const {
                return set.end();
            }
    };
}