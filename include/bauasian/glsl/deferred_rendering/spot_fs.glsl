#version 420 core
#include "../bindings.glsl"
#include "../common/lights.glsl"
#include "../common/attenuation.glsl"

layout (std140, binding = BUFFER_CAMERA_BINDING) uniform CameraBuffer
{
    mat4 projection_matrix;
    mat4 view_matrix;
    vec3 position;
	float near;
	float far;
} camera;

layout (std140, binding = BUFFER_SPOT_LIGHT_BINDING) uniform SpotLightBuffer
{
    SpotLight spot_light;
};

layout (binding = DEFERRED_ALBEDO_BINDING) uniform sampler2D albedo_buffer;
layout (binding = DEFERRED_SPECULAR_BINDING) uniform sampler2D specular_buffer;
layout (binding = DEFERRED_NORMAL_BINDING) uniform sampler2D normal_buffer;
layout (binding = DEFERRED_POSITION_BINDING) uniform sampler2D position_buffer;

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

    vec3 view_dir = normalize(camera.position - fragment_position);


    vec3 light_ray = spot_light.position - fragment_position;
    float distance = length(light_ray);

    vec3 light_ray_direction = normalize(light_ray);
    float spot_effect = dot(normalize(-spot_light.direction), light_ray_direction);
    float inner_cosine = cos(spot_light.inner_angle);
    float outer_cosine = cos(spot_light.outer_angle);

    float attenuation = getLightAttenuation(distance, spot_light.attenuation);

    float falloff = clamp((outer_cosine - spot_effect) / (outer_cosine - inner_cosine), 0.f, 1.f);

    vec3 diffuse = processDiffuseLight(fragment_normal, light_ray_direction, spot_light.diffuse_color) * fragment_diffuse;
    vec3 specular = processSpecularLight(fragment_normal, light_ray_direction, spot_light.specular_color,
                                         view_dir, fragment_shininess) * fragment_specular;

	out_color = vec4(diffuse + specular, 1.f) * falloff * attenuation;
}
