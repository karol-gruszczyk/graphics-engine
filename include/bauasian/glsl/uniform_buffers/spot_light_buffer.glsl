#include "../bindings.glsl"

layout (std140, binding = BUFFER_SPOT_LIGHT_BINDING) uniform SpotLightBuffer
{
	mat4 model_matrix;
	vec3 diffuse_color;
	vec3 specular_color;
	vec3 position;
	vec3 direction;
	vec3 attenuation;
	float inner_angle;
	float outer_angle;
} spot_light;
