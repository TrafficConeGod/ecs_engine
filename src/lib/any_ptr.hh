#pragma once

namespace newt::lib {
    class any_ptr {
        void* ptr;
        public:
            inline any_ptr() : ptr(nullptr) {}

            template<typename T>
            inline any_ptr(T* ptr_) : ptr(ptr_) {}

            template<typename T>
            inline const T* get() const {
                return (const T*)ptr;
            }

            template<typename T>
            inline T* get() {
                return (T*)ptr;
            }
    };
};