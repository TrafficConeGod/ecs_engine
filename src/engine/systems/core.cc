#include "core.hh"
#include "routines/render.hh"
#include <mutex>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shader_util.hh"
#include "lib/timing.hh"
#include "engine/components/mesh_2d.hh"
#include "engine/components/rigid_transform_2d.hh"
#include "engine/components/rotational_transform_2d.hh"

using namespace newt;
using namespace engine;

namespace chrono = std::chrono;

auto renderer_init(database& db) {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    auto win = glfwCreateWindow(1280, 720, "Test", NULL, NULL);
    if (win == NULL) {
        glfwTerminate();
        throw std::runtime_error("Failed to open GLFW window");
    }
    glfwMakeContextCurrent(win);
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        throw std::runtime_error("Failed to initialize GLEW");
    }

    glfwSetInputMode(win, GLFW_STICKY_KEYS, GL_TRUE);

    glClearColor(0.f, 0.f, 0.f, 0.0f);

    GLuint vertex_array_id;
    glGenVertexArrays(1, &vertex_array_id);
    glBindVertexArray(vertex_array_id);

    GLuint vertex_id = 0;
    glGenBuffers(1, &vertex_id);

    db.default_shader().load();
    glUseProgram(db.default_shader().program_id());

    struct result {
        GLFWwindow* win;
        GLuint vertex_id;
    };
    return result{
        win,
        vertex_id,
    };
}

void systems::core(database* db_ptr) {
    auto& db = *db_ptr;
    auto [win, vertex_id] = renderer_init(db);
    auto clock = chrono::steady_clock::now();
    chrono::nanoseconds delta_time(lib::GAME_DELTA_TIME);

    for (;;) {
        // Before rendering we load all shaders
        {
            std::scoped_lock lock(db.components<components::shader>().mutex());
            for (auto& shader : db.components<components::shader>()) {
                if (!shader.resource->loaded()) {
                    shader.resource->load();
                }
            }
        }

        std::scoped_lock lock(db.entities().mutex());
        {
            std::scoped_lock lock2(db.components<components::rigid_transform_2d>().mutex(), db.components<components::rotational_transform_2d>().mutex(), db.components<components::mesh_2d>().mutex(), db.components<components::shader>().mutex());
            if (!systems::routines::render(db, win, vertex_id)) {
                break;
            }
        }

        auto actual_delta_time = chrono::steady_clock::now() - clock;
        lib::match_delta_time(lib::GAME_DELTA_TIME, actual_delta_time);
        delta_time = chrono::steady_clock::now() - clock;
        clock = chrono::steady_clock::now();
    }
}