#version 330

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

struct Material
{
	sampler2D diffuse_texture;
};

in vec3 position;
in vec2 texture_coord;
in vec3 normal;

out vec4 out_color;

uniform Material material;

uniform vec3 camera_position;
uniform DirectionalLight dir_light;

vec3 light_color = vec3(1.f, 1.f, 1.f);


void main()
{
	float ambient_strength = 0.1f;

	vec3 ambient = ambient_strength * light_color;

	vec3 diffuse = max(dot(normal, -dir_light.direction), 0.f) * light_color;

	vec3 view_dir = normalize(camera_position - position);
	vec3 reflect_dir = reflect(dir_light.direction, normal);
	vec3 specular = pow(max(dot(view_dir, reflect_dir), 0.0), 64) * light_color;

	vec4 object_color = texture2D(material.diffuse_texture, texture_coord);

	out_color = vec4(ambient + diffuse + specular, 1.f) * object_color;
}
