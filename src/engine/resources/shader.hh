#pragma once
#include <string>
#include <initializer_list>
#include <GL/glew.h>

namespace newt::engine::resources {
    class shader {
        std::string_view vertex_shader;
        std::string_view fragment_shader;

        bool loaded_;
        GLuint program_id_;
        public:
            inline shader(std::string_view vertex_shader_, std::string_view fragment_shader_, std::initializer_list<std::string_view> uniform_names) : vertex_shader(vertex_shader_), fragment_shader(fragment_shader_) {}

            // We have to load the shader seperately from the constructor because OpenGL can't load shaders from a seperate thread.
            void load();

            inline bool loaded() const { return loaded_; }

            inline GLuint program_id() const { return program_id_; }
    };
}