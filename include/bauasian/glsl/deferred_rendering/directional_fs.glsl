#version 330 core
#include "../common/lights.glsl"
#include "../utils/luminance.glsl"

layout(std140) uniform SceneBuffer
{
    vec3 camera_position;
};

uniform sampler2D albedo_buffer;
uniform sampler2D specular_buffer;
uniform sampler2D normal_buffer;
uniform sampler2D position_buffer;

layout (std140) uniform DirectionalLightBuffer
{
    DirectionalLight dir_light;
};

in vec2 texture_coord;

out vec4 out_color;


void main()
{
    vec3 fragment_diffuse = texture(albedo_buffer, texture_coord).rgb;
    vec4 fragment_specular_buffer = texture(specular_buffer, texture_coord);
    vec3 fragment_specular = fragment_specular_buffer.rgb;
    float fragment_shininess = 1.f / fragment_specular_buffer.a;
    vec3 fragment_normal = texture(normal_buffer, texture_coord).rgb;
    vec3 fragment_position = texture(position_buffer, texture_coord).rgb;

    vec3 view_dir = normalize(camera_position - fragment_position);
	vec3 light_ray_direction = normalize(-dir_light.direction);
	vec3 diffuse = processDiffuseLight(fragment_normal, light_ray_direction, dir_light.diffuse_color) * fragment_diffuse;
	vec3 specular = processSpecularLight(fragment_normal, light_ray_direction, dir_light.specular_color,
	                                     view_dir, fragment_shininess) * fragment_specular;

    vec3 result_color = diffuse + specular;
	out_color = vec4(result_color, 1.f);
}
