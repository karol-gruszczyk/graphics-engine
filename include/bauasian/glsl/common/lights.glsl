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
	mat4 model_matrix;
	vec3 diffuse_color;
	vec3 specular_color;
	vec3 position;
	vec3 direction;
	vec3 attenuation;
	float inner_angle;
	float outer_angle;
};
