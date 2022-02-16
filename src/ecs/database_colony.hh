#pragma once
#include "plf_colony.hh"
#include <memory>
#include <mutex>
#include <stdexcept>

namespace newt::ecs {
    // Dont normally copy this
    template<typename T>
    class database_colony {
        // Ugly hack to make this copy constructible
        std::shared_ptr<std::mutex> mutex_ = std::make_shared<std::mutex>();
        plf::colony<T> colony;
        bool listening_for_inserted_values_ = false;
        std::vector<T*> inserted_values;
        public:
            inline std::mutex& mutex() {
                return *mutex_;
            }

            // Whether or not to listen for insertion and add the values to the inserted_values vector
            inline bool& listening_for_inserted_values() {
                return listening_for_inserted_values_;
            }

            inline std::size_t size() const { return colony.size(); }
        
            T* insert(const T& value) {
                // If we are listening for inserted values, add the index to the inserted_values vector
                if (listening_for_inserted_values_) {
                    inserted_values.push_back(&(*colony.insert(value)));
                    return inserted_values.back();
                } else {
                    return &(*colony.insert(value));
                }
            }

            void erase(T* value) {
                // If we are listening for inserted values, remove the index from the inserted_values vector
                if (listening_for_inserted_values_) {
                    // Since std::erase_if would be less efficient, we have to do it manually
                    for (auto it = inserted_values.begin(); it != inserted_values.end(); ++it) {
                        if (*it == value) {
                            inserted_values.erase(it);
                            break;
                        }
                    }
                }
                colony.erase(colony.get_iterator(value));
            }

            void clear_inserted_values() {
                inserted_values.clear();
            }

            std::vector<T*> copy_inserted_values() const {
                if (!listening_for_inserted_values_) {
                    throw std::runtime_error("listening_for_inserted_values must be true to use this function");
                }
                return inserted_values;
            }

            inline auto begin() {
                return colony.begin();
            }

            inline auto end() {
                return colony.end();
            }

            inline auto begin() const {
                return colony.begin();
            }

            inline auto end() const {
                return colony.end();
            }
    };
}