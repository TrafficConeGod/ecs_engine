#include "component.hh"
using namespace newt::ecs;

std::size_t next_component_id;

std::size_t head_component::next_id() {
    return next_component_id++;
}