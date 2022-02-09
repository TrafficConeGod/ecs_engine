#pragma once
#include "lib/vector.hh"
#include <array>
#include <vector>
#include <initializer_list>

namespace newt::resources {
    class mesh_2d {
        public:
            using vertex = lib::vector<float, 2>;
            struct triangle {
                std::array<vertex, 3> vertices;
            };
        private:
            std::vector<triangle> triangles_;
        public:
            inline mesh_2d() = default;
            mesh_2d(const mesh_2d&) = delete;
            mesh_2d(mesh_2d&&) = delete;
            mesh_2d& operator=(const mesh_2d&) = delete;
            inline mesh_2d(std::initializer_list<triangle> list) {
                std::copy(list.begin(), list.end(), triangles_.begin());
            }
            inline mesh_2d(std::vector<triangle>&& triangles__) : triangles_(std::move(triangles__)) {}

            inline const std::vector<triangle>& triangles() const {
                return triangles_;
            }
    };
};