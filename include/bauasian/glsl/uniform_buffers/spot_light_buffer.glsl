#include "../bindings.glsl"
#include "../common/lights.glsl"

layout (std140, binding = BUFFER_SPOT_LIGHT_BINDING) uniform SpotLightBuffer
{
    SpotLight spot_light;
};
