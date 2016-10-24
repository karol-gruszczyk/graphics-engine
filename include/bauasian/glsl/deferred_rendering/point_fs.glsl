#version 330 core
#include "../common/lights.glsl"
#include "../common/attenuation.glsl"

layout (std140) uniform SceneBuffer
{
    vec3 camera_position;
};

layout (std140) uniform PointLightBuffer
{
    PointLight point_light;
};

uniform sampler2D albedo_buffer;
uniform sampler2D specular_buffer;
uniform sampler2D normal_buffer;
uniform sampler2D position_buffer;

uniform vec2 screen_size;

out vec4 out_color;


void main()
{
    vec2 texture_coord = gl_FragCoord.xy / screen_size;
    vec3 fragment_diffuse = texture(albedo_buffer, texture_coord).rgb;
    vec4 fragment_specular_buffer = texture(specular_buffer, texture_coord);
    vec3 fragment_specular = fragment_specular_buffer.rgb;
    float fragment_shininess = 1.f / fragment_specular_buffer.a;
    vec3 fragment_normal = texture(normal_buffer, texture_coord).rgb;
    vec3 fragment_position = texture(position_buffer, texture_coord).rgb;
    vec3 fragment_ambient = fragment_diffuse;

    vec3 view_dir = normalize(camera_position - fragment_position);

	vec3 light_ray = point_light.position - fragment_position;
	float distance = length(light_ray);

    float attenuation = getLightAttenuation(distance, point_light.attenuation);
    vec3 light_ray_direction = normalize(light_ray);

    vec3 ambient = processAmbientLight(point_light.ambient_color) * fragment_ambient;
    vec3 diffuse = processDiffuseLight(fragment_normal, light_ray_direction, point_light.diffuse_color) * fragment_diffuse;
    vec3 specular = processSpecularLight(fragment_normal, light_ray_direction, point_light.specular_color,
                                         view_dir, fragment_shininess) * fragment_specular;

	out_color = vec4(ambient + diffuse + specular, 1.f) * attenuation;
}
