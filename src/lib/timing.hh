#pragma once
#include <thread>
#include <chrono>

namespace newt::lib {
    using float_duration = std::chrono::duration<float>;

    constexpr std::chrono::milliseconds GAME_DELTA_TIME(16);

    void match_delta_time(const std::chrono::nanoseconds& delta_time, const std::chrono::nanoseconds& actual_delta_time);
};