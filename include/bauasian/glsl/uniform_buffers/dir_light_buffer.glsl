#include "../bindings.glsl"

layout (std140, binding = BUFFER_DIRECTIONAL_LIGHT_BINDING) uniform DirectionalLightBuffer
{
	vec3 diffuse_color;
	vec3 specular_color;
	vec3 direction;
	int use_shadow_map;
} dir_light;
