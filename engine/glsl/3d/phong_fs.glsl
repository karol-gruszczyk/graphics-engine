#version 330
#define MAX_POINT_LIGHTS 8
#define MAX_SPOT_LIGHTS 8

struct DirectionalLight
{
	vec3 color;
	vec3 direction;
};

struct PointLight
{
	vec3 color;
	vec3 position;
	float range;
};

struct SpotLight
{
	vec3 color;
	vec3 position;
	vec3 direction;
	float range;
	float inner_angle;
	float outer_angle;
};

in vec3 position;
in vec2 texture_coord;
in vec3 normal;

out vec4 out_color;

uniform sampler2D diffuse_texture;

uniform vec3 camera_position;
uniform DirectionalLight dir_light;
uniform PointLight point_lights[MAX_POINT_LIGHTS];
uniform uint num_point_lights;
uniform SpotLight spot_lights[MAX_SPOT_LIGHTS];
uniform uint num_spot_lights;

float ambient_strength = 0.1f;
float specular_power = 32;

vec3 processDirectionalLight(DirectionalLight dir_light);
vec3 processPointLight(PointLight point_light);
vec3 processSpotLight(SpotLight spot_light);


void main()
{
	vec4 object_color = texture2D(diffuse_texture, texture_coord);

	vec3 light_color = processDirectionalLight(dir_light);
	for (uint i = 0; i < num_point_lights; i++)
		light_color += processPointLight(point_lights[i]);
	for (uint i = 0; i < num_spot_lights; i++)
		light_color += processSpotLight(spot_lights[i]);

	out_color = vec4(light_color, 1.f) * object_color;
}

vec3 processAmbientLight(vec3 light_color)
{
	return ambient_strength * light_color;
}

vec3 processDiffuseLight(vec3 light_ray_direction, vec3 light_color)
{
	return max(dot(normal, light_ray_direction), 0.f) * light_color;
}

vec3 processSpecularLight(vec3 light_ray_direction, vec3 light_color)
{
	vec3 view_dir = normalize(camera_position - position);
	vec3 reflect_dir = reflect(-light_ray_direction, normal);
	return pow(max(dot(view_dir, reflect_dir), 0.0), specular_power) * light_color;
}

vec3 processDirectionalLight(DirectionalLight dir_light)
{
	vec3 light_ray_direction = normalize(-dir_light.direction);
	vec3 ambient = processAmbientLight(dir_light.color);
	vec3 diffuse = processDiffuseLight(light_ray_direction, dir_light.color);
	vec3 specular = processSpecularLight(light_ray_direction, dir_light.color);

	return ambient + diffuse + specular;
}

vec3 processPointLight(PointLight point_light)
{
	float distance = length(point_light.position - position);

	float constant_factor = 1.f; float linear_factor = 2 / point_light.range; float quadratic_factor = 1 / pow(point_light.range, 2);
	float attenuation = 1 / ((constant_factor) + (linear_factor * distance) + (quadratic_factor * pow(distance, 2)));
	vec3 light_ray_direction = normalize(point_light.position - position);

	vec3 ambient = processAmbientLight(point_light.color);
	vec3 diffuse = processDiffuseLight(light_ray_direction, point_light.color);
	vec3 specular = processSpecularLight(light_ray_direction, point_light.color);

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

	float constant_factor = 1.f; float linear_factor = 2 / spot_light.range; float quadratic_factor = 1 / pow(spot_light.range, 2);
	float attenuation = 1 / ((constant_factor) + (linear_factor * distance) + (quadratic_factor * pow(distance, 2)));

	float falloff = clamp((outer_cosine - spot_effect) / (outer_cosine - cos(spot_light.inner_angle)), 0.f, 1.f);

	vec3 ambient = processAmbientLight(spot_light.color);
	vec3 diffuse = processDiffuseLight(light_ray_direction, spot_light.color);
	vec3 specular = processSpecularLight(light_ray_direction, spot_light.color);

	return falloff * attenuation * (ambient + diffuse + specular);
}
