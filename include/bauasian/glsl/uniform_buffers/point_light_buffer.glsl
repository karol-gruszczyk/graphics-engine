#include "../bindings.glsl"
#include "../common/lights.glsl"

layout (std140, binding = BUFFER_POINT_LIGHT_BINDING) uniform PointLightBuffer
{
    PointLight point_light;
};
