#include "../bindings.glsl"

layout(std140, binding = BUFFER_MATERIAL_BINDING) uniform Material
{
	vec4 diffuse_color;
	vec4 specular_color;

	int use_diffuse_texture;
	int use_specular_texture;
	int use_normal_texture;
	int use_displacement_texture;
	int use_opacity_texture;

	float shininess;
} material;
