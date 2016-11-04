#include "../bindings.glsl"

layout (std140, binding = BUFFER_POINT_LIGHT_BINDING) uniform PointLightBuffer
{
	mat4 model_matrix;
	vec3 diffuse_color;
	vec3 specular_color;
	vec3 position;
	vec3 attenuation;
} point_light;
