#include "../bindings.glsl"
#include "../common/lights.glsl"

layout (std140, binding = BUFFER_DIRECTIONAL_LIGHT_BINDING) uniform DirectionalLightBuffer
{
    DirectionalLight dir_light;
};
