#include "render.hh"
#include "ecs/entity.hh"
#include "engine/components/mesh_2d.hh"
#include "engine/components/rigid_transform_2d.hh"
#include "engine/components/shader.hh"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cstdio>

using namespace newt;
using namespace engine;

bool systems::routines::render(const database& db, GLFWwindow* const win, const GLuint vertex_id) {
    for (auto& mesh : db.components<components::mesh_2d>()) {
        auto& entity = *mesh.entity_ptr;
        if (entity.has_component<components::rigid_transform_2d>()) {
            auto& shader_res = entity.has_component<components::shader>() ? *entity.component<components::shader>()->resource : db.default_shader();
            glUseProgram(shader_res.program_id());

            auto& rtf = *entity.component<components::rigid_transform_2d>();

            auto& triangles = mesh.resource->triangles();
            
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, vertex_id);
            glBufferData(GL_ARRAY_BUFFER, triangles.size() * sizeof(resources::mesh_2d::triangle), triangles.data(), GL_STATIC_DRAW);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
            
            glDrawArrays(GL_TRIANGLES, 0, triangles.size() * 3);

            glDisableVertexAttribArray(0);
            
            // glEnableVertexAttribArray(1);
            // glBindBuffer(GL_ARRAY_BUFFER, vertex_id);
            // glBufferData(GL_ARRAY_BUFFER, triangles.size() * sizeof(newt::resources::mesh_2d::triangle), triangles.data(), GL_STATIC_DRAW);
            // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
            
            // glDrawArrays(GL_TRIANGLES, 0, triangles.size() * 3);

            // glDisableVertexAttribArray(1);

        }
    }

    glfwSwapBuffers(win);
    
    glfwPollEvents();

    if (glfwWindowShouldClose(win)) {
        return false;
    }
    return true;
}