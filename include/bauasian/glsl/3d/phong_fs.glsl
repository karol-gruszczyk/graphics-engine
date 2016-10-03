#version 330
#include "lights.glsl"

in vec3 position;
in vec2 texture_coord;
in vec3 normal;

out vec4 out_color;

uniform Material material;

uniform vec3 camera_position;
uniform DirectionalLight dir_lights[MAX_DIR_LIGHTS];
uniform uint num_dir_lights;
uniform PointLight point_lights[MAX_POINT_LIGHTS];
uniform uint num_point_lights;
uniform SpotLight spot_lights[MAX_SPOT_LIGHTS];
uniform uint num_spot_lights;


void main()
{
    setFragmentColors(material, texture_coord);

	vec3 object_color = vec3(0.f, 0.f, 0.f);
	for (uint i = uint(0); i < num_dir_lights; i++)
		object_color += processDirectionalLight(dir_lights[i], material, position, normal, camera_position);
	for (uint i = uint(0); i < num_point_lights; i++)
		object_color += processPointLight(point_lights[i], material, position, normal, camera_position);
	for (uint i = uint(0); i < num_spot_lights; i++)
		object_color += processSpotLight(spot_lights[i], material, position, normal, camera_position);

	out_color = vec4(object_color, 1.f);
}