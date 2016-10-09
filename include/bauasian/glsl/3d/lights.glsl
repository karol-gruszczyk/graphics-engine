#include "globals.glsl"


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
	vec3 position; float _offset;
	float range;
	float attenuation_constant;
	float attenuation_linear;
	float attenuation_quadratic;
};

struct SpotLight
{
	vec3 ambient_color;
	vec3 diffuse_color;
	vec3 specular_color;
	vec3 position; float _offset;
	float range;
	float attenuation_constant;
	float attenuation_linear;
	float attenuation_quadratic;
	vec3 direction; float _offset1;
	float inner_angle;
	float outer_angle;
};
