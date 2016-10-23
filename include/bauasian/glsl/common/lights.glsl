#include "blinn_phong.glsl"


struct DirectionalLight
{
	vec3 ambient_color;
	vec3 diffuse_color;
	vec3 specular_color;
	vec3 direction;
};

struct PointLight
{
	vec3 ambient_color;
	vec3 diffuse_color;
	vec3 specular_color;
	mat4 model_matrix;
	vec3 position;
	float range;
	vec3 attenuation;
};

struct SpotLight
{
	vec3 ambient_color;
	vec3 diffuse_color;
	vec3 specular_color;
	mat4 model_matrix;
	vec3 position;
	float range;
	vec3 attenuation;
	vec3 direction;
	float inner_angle;
	float outer_angle;
};
