// Since the compiler I'm using doesn't have jthread support, I have to make this class
#pragma once
#include <thread>

namespace newt::lib {
    class jthread {
        std::thread worker;
        public:
            template<typename _Callable, typename... _Args>
            explicit jthread(_Callable&& func, _Args&&... args) : worker(std::move(func), std::move(args)...) {}
            ~jthread() { worker.join(); }
    };
};