#pragma once

#define USE_MACRO_ON_COMPONENTS(macro) \
macro(rigid_transform_2d) \
macro(rotational_transform_2d) \
macro(mesh_2d)

namespace newt::components {
    struct rigid_transform_2d;
    struct rotational_transform_2d;
    struct mesh_2d;
};