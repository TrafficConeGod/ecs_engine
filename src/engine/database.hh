#pragma once
#include "ecs/database.hh"
#include "components/rigid_transform_2d.hh"
#include "components/rotational_transform_2d.hh"
#include "components/mesh_2d.hh"
#include "components/shader.hh"

#define NEWT_ENGINE_USE_MACRO_ON_COMPONENTS(macro) \
macro(rigid_transform_2d) \
macro(rotational_transform_2d) \
macro(mesh_2d) \
macro(shader)

#define NEWT_ENGINE_SPECIALIZE_COMPONENT_TYPE(name) \
template<> \
constexpr const newt::ecs::database_colony<newt::engine::components::name>& newt::engine::database::components_impl() const { \
    return name##_colony; \
}

namespace newt::engine {
    class database : public ecs::database {
        resources::shader default_shader_{
            "shaders/default/vertex.glsl",
            "shaders/default/fragment.glsl",
            {
                "position",
                "scale"
            }
        };
        NEWT_ENGINE_USE_MACRO_ON_COMPONENTS(MAKE_COMPONENT_COLONY)
        OVERRIDE_COMPONENTS_TEMPLATE
        public:
            void erase_entity(ecs::entity* ent);
            ecs::entity* copy_entity(const ecs::entity& ent);

            inline resources::shader& default_shader() { return default_shader_; }
            inline const resources::shader& default_shader() const { return default_shader_; }
    };
}

NEWT_ENGINE_USE_MACRO_ON_COMPONENTS(NEWT_ENGINE_SPECIALIZE_COMPONENT_TYPE)