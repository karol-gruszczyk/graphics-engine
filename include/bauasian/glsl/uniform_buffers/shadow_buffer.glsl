#include "../bindings.glsl"

layout (std140, binding = BUFFER_SHADOW_BINDING) uniform ShadowBuffer
{
    mat4 light_space_matrix;
} shadow;
