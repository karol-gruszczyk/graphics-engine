#version 330 core
#include "../common/lights.glsl"

layout (std140) uniform SceneBuffer
{
    vec3 camera_position;
};

layout (std140) uniform SpotLightBuffer
{
    SpotLight spot_light;
};

uniform sampler2D albedo_buffer;
uniform sampler2D specular_buffer;
uniform sampler2D normal_buffer;
uniform sampler2D position_buffer;

uniform vec3 light_position;
uniform vec3 light_direction;
uniform vec3 light_diffuse_color;
uniform vec3 light_specular_color;
uniform vec3 light_attenuation;
uniform float light_inner_angle;
uniform float light_outer_angle;

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
    vec3 fragment_ambient = fragment_diffuse;

    vec3 view_dir = normalize(camera_position - fragment_position);


    vec3 light_ray = spot_light.position - fragment_position;
    float distance = length(light_ray);

    vec3 light_ray_direction = normalize(light_ray);
    float spot_effect = dot(normalize(-spot_light.direction), light_ray_direction);
    float outer_cosine = cos(spot_light.outer_angle);

    float attenuation = 1.f / ((spot_light.attenuation.r) + (spot_light.attenuation.g * distance)
                        + (spot_light.attenuation.b * distance * distance));

    float falloff = clamp((outer_cosine - spot_effect) / (outer_cosine - cos(spot_light.inner_angle)), 0.f, 1.f);

    vec3 ambient = processAmbientLight(spot_light.ambient_color) * fragment_ambient;
    vec3 diffuse = processDiffuseLight(fragment_normal, light_ray_direction, spot_light.diffuse_color) * fragment_diffuse;
    vec3 specular = processSpecularLight(fragment_normal, light_ray_direction, spot_light.specular_color,
                                         view_dir, fragment_shininess) * fragment_specular;

	out_color = vec4(ambient + diffuse + specular, falloff * attenuation);
}
