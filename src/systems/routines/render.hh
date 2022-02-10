#pragma once
#include "ecs/database.hh"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace newt::systems::routines {
    bool render(const ecs::database& db, GLFWwindow* window, GLuint program_id, GLuint vertex_id);
};