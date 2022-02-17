#include "engine/resources/shader.hh"
#include "shader_util.hh"

using namespace newt::engine::resources;

void shader::load() {
    loaded_ = true;
    program_id_ = load_shaders(vertex_shader.data(), fragment_shader.data());
}