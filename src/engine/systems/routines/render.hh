#pragma once
#include "engine/database.hh"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace newt::engine::systems::routines {
    bool render(const engine::database& db, GLFWwindow* const window, GLuint const program_id, GLuint const vertex_id);
};