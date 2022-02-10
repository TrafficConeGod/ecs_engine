#include "timing.hh"
#include <iostream>

using namespace newt;
namespace chrono = std::chrono;

void lib::match_delta_time(const chrono::nanoseconds& delta_time, const chrono::nanoseconds& actual_delta_time) {
    if (actual_delta_time < delta_time) {
        std::this_thread::sleep_for(delta_time - actual_delta_time);
    }
}