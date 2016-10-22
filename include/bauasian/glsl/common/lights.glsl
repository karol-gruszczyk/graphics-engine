#include "../globals.glsl"
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

vec3 processDirectionalLight(DirectionalLight dir_light, vec3 normal, vec3 view_dir, float shininess)
{
	vec3 light_ray_direction = normalize(-dir_light.direction);
	vec3 ambient = processAmbientLight(dir_light.ambient_color);
	vec3 diffuse = processDiffuseLight(normal, light_ray_direction, dir_light.diffuse_color);
	vec3 specular = processSpecularLight(normal, light_ray_direction, dir_light.specular_color, view_dir, shininess);

	return ambient + diffuse + specular;
}
/*
vec3 processPointLight(PointLight point_light)
{
	float distance = length(point_light.position - position);

	float attenuation = 1 / ((point_light.attenuation_constant) + (point_light.attenuation_linear * distance)
	 + (point_light.attenuation_quadratic * distance * distance));
	vec3 light_ray_direction = normalize(point_light.position - position);

	vec3 ambient = processAmbientLight(point_light.ambient_color);
	vec3 diffuse = processDiffuseLight(light_ray_direction, point_light.diffuse_color);
	vec3 specular = processSpecularLight(light_ray_direction, point_light.specular_color);

	return attenuation * (ambient + diffuse + specular);
}

vec3 processSpotLight(SpotLight spot_light)
{
	float distance = length(spot_light.position - position);

	vec3 light_ray_direction = normalize(spot_light.position - position);
	float spot_effect = dot(normalize(-spot_light.direction), light_ray_direction);
	float outer_cosine = cos(spot_light.outer_angle);

	if (spot_effect < outer_cosine)
		return vec3(0.f);

	float attenuation = 1 / ((spot_light.attenuation_constant) + (spot_light.attenuation_linear * distance)
    	 + (spot_light.attenuation_quadratic * distance * distance));

	float falloff = clamp((outer_cosine - spot_effect) / (outer_cosine - cos(spot_light.inner_angle)), 0.f, 1.f);

	vec3 ambient = processAmbientLight(spot_light.ambient_color);
	vec3 diffuse = processDiffuseLight(light_ray_direction, spot_light.diffuse_color);
	vec3 specular = processSpecularLight(light_ray_direction, spot_light.specular_color);

	return falloff * attenuation * (ambient + diffuse + specular);
}
*/