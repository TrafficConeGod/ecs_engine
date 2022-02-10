#include "timing.hh"

using namespace newt;

void lib::match_delta_time(const std::chrono::nanoseconds& delta_time, const std::chrono::nanoseconds& actual_delta_time) {
    if (actual_delta_time < delta_time) {
        std::this_thread::sleep_for(delta_time - actual_delta_time);
    }
}