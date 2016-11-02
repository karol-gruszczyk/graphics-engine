#include "blinn_phong.glsl"


struct DirectionalLight
{
	vec3 diffuse_color;
	vec3 specular_color;
	vec3 direction;
};

struct PointLight
{
	mat4 model_matrix;
	vec3 diffuse_color;
	vec3 specular_color;
	vec3 position;
	vec3 attenuation;
};

struct SpotLight
{
	vec3 diffuse_color;
	vec3 specular_color;
	mat4 model_matrix;
	vec3 position; float a;
	float range;
	vec3 attenuation; float b;
	vec3 direction;
	float inner_angle;
	float outer_angle;
};
