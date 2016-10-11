#version 330 core
#include "lights.glsl"

layout(std140) uniform SceneBuffer
{
    DirectionalLight dir_lights[MAX_DIR_LIGHTS];
    PointLight point_lights[MAX_POINT_LIGHTS];
    SpotLight spot_lights[MAX_SPOT_LIGHTS];
    vec3 camera_position;
    int num_dir_lights;
    int num_point_lights;
    int num_spot_lights;
};

layout(std140) uniform Material
{
	vec4 ambient_color;
	vec4 diffuse_color;
	vec4 specular_color;

	int use_ambient_texture;
	int use_diffuse_texture;
	int use_specular_texture;
	int use_normal_texture;

	float shininess;
} material;

uniform sampler2D ambient_texture;
uniform sampler2D diffuse_texture;
uniform sampler2D specular_texture;
uniform sampler2D normal_texture;

in vec3 position;
in vec2 texture_coord;
in vec3 normal;
in mat3 tbn;

out vec4 out_color;

vec3 fragment_ambient_color;
vec3 fragment_diffuse_color;
vec3 fragment_specular_color;
vec3 fragment_normal;

void setFragmentColors(vec2 texture_coord);
vec3 processAmbientLight(vec3 light_color);
vec3 processDiffuseLight(vec3 light_ray_direction, vec3 light_color);
vec3 processSpecularLight(vec3 light_ray_direction, vec3 light_color);
vec3 processDirectionalLight(DirectionalLight dir_light);
vec3 processPointLight(PointLight point_light);
vec3 processSpotLight(SpotLight spot_light);


void main()
{
    setFragmentColors(texture_coord);

	vec3 object_color = vec3(0.f, 0.f, 0.f);
	for (int i = 0; i < num_dir_lights; i++)
		object_color += processDirectionalLight(dir_lights[i]);
	for (int i = 0; i < num_point_lights; i++)
		object_color += processPointLight(point_lights[i]);
	for (int i = 0; i < num_spot_lights; i++)
		object_color += processSpotLight(spot_lights[i]);

	out_color = vec4(object_color, 1.f);
}

void setFragmentColors(vec2 texture_coord)
{
	if (material.use_ambient_texture == 1)
		fragment_ambient_color = texture2D(ambient_texture, texture_coord).rgb;
	else
	    fragment_ambient_color = material.ambient_color.rgb;

	if (material.use_diffuse_texture == 1)
		fragment_diffuse_color = texture2D(diffuse_texture, texture_coord).rgb;
	else
	    fragment_diffuse_color = material.diffuse_color.rgb;

	if (material.use_specular_texture == 1)
		fragment_specular_color = texture2D(specular_texture, texture_coord).rgb;
	else
	    fragment_specular_color = material.specular_color.rgb;

	if (material.use_normal_texture == 1)
		fragment_normal = tbn * (texture2D(normal_texture, texture_coord).rgb * 2.f - 1.f);
	else
	    fragment_normal = normal;
}

vec3 processAmbientLight(vec3 light_color)
{
	return AMBIENT_STRENGTH * light_color * fragment_ambient_color;
}

vec3 processDiffuseLight(vec3 light_ray_direction, vec3 light_color)
{
	return max(dot(fragment_normal, light_ray_direction), 0.f) * light_color * fragment_diffuse_color;
}

vec3 processSpecularLight(vec3 light_ray_direction, vec3 light_color)
{
	if (material.shininess == 0)
		return vec3(0.f, 0.f, 0.f);
	vec3 view_dir = normalize(camera_position - position);
	vec3 reflect_dir = reflect(-light_ray_direction, fragment_normal);
	return pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess) * light_color * fragment_specular_color;
}

vec3 processDirectionalLight(DirectionalLight dir_light)
{
	vec3 light_ray_direction = normalize(-dir_light.direction);
	vec3 ambient = processAmbientLight(dir_light.ambient_color);
	vec3 diffuse = processDiffuseLight(light_ray_direction, dir_light.diffuse_color);
	vec3 specular = processSpecularLight(light_ray_direction, dir_light.specular_color);

	return ambient + diffuse + specular;
}

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
	if (distance > spot_light.range * 2)
		return vec3(0.0, 0.0, 0.0);

	vec3 light_ray_direction = normalize(spot_light.position - position);
	float spot_effect = dot(normalize(-spot_light.direction), light_ray_direction);
	float outer_cosine = cos(spot_light.outer_angle);

	if (spot_effect < outer_cosine)
		return vec3(0.f, 0.f, 0.f);

	float attenuation = 1 / ((spot_light.attenuation_constant) + (spot_light.attenuation_linear * distance)
    	 + (spot_light.attenuation_quadratic * distance * distance));

	float falloff = clamp((outer_cosine - spot_effect) / (outer_cosine - cos(spot_light.inner_angle)), 0.f, 1.f);

	vec3 ambient = processAmbientLight(spot_light.ambient_color);
	vec3 diffuse = processDiffuseLight(light_ray_direction, spot_light.diffuse_color);
	vec3 specular = processSpecularLight(light_ray_direction, spot_light.specular_color);

	return falloff * attenuation * (ambient + diffuse + specular);
}
