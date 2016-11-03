#version 420 core
#include "../bindings.glsl"
#include "../common/lights.glsl"
#include "../utils/luminance.glsl"

layout(std140, binding = BUFFER_CAMERA_BINDING) uniform CameraBuffer
{
    mat4 projection_matrix;
    mat4 view_matrix;
    vec3 position;
	float near;
	float far;
} camera;

layout (binding = DEFERRED_ALBEDO_BINDING) uniform sampler2D albedo_buffer;
layout (binding = DEFERRED_SPECULAR_BINDING) uniform sampler2D specular_buffer;
layout (binding = DEFERRED_NORMAL_BINDING) uniform sampler2D normal_buffer;
layout (binding = DEFERRED_POSITION_BINDING) uniform sampler2D position_buffer;
layout (binding = DEFERRED_SHADOW_MAP_BINDING) uniform sampler2DShadow shadow_map;

layout (std140, binding = BUFFER_DIRECTIONAL_LIGHT_BINDING) uniform DirectionalLightBuffer
{
    DirectionalLight dir_light;
};

layout (std140, binding = BUFFER_SHADOW_CAMERA_BINDING) uniform ShadowCameraBuffer
{
    mat4 projection_matrix;
    mat4 view_matrix;
    vec3 position;
	float near;
	float far;
} shadow_camera;

in vec2 texture_coord;

out vec4 out_color;


void main()
{
    float shadow_depth = 1.f;
    vec3 frag_position = texture(position_buffer, texture_coord).rgb;
    if (dir_light.use_shadow_map == 1)
    {
        vec4 shadow_position = shadow_camera.projection_matrix * shadow_camera.view_matrix * vec4(frag_position, 1.f);
        shadow_position.xyz /= shadow_position.w;
        shadow_position.xyz = shadow_position.xyz * 0.5f + 0.5f;
        shadow_depth = texture(shadow_map, shadow_position.xyz);
        if (shadow_depth == 0.f)
            discard;
    }
    vec3 frag_diffuse = texture(albedo_buffer, texture_coord).rgb;
    vec4 frag_specular_buffer = texture(specular_buffer, texture_coord);
    vec3 frag_specular = frag_specular_buffer.rgb;
    float frag_shininess = 1.f / frag_specular_buffer.a;
    vec3 frag_normal = texture(normal_buffer, texture_coord).rgb;

    vec3 view_dir = normalize(camera.position - frag_position);
	vec3 light_ray_direction = normalize(-dir_light.direction);
	vec3 diffuse = processDiffuseLight(frag_normal, light_ray_direction, dir_light.diffuse_color) * frag_diffuse;
	vec3 specular = processSpecularLight(frag_normal, light_ray_direction, dir_light.specular_color,
	                                     view_dir, frag_shininess) * frag_specular;

    vec3 result_color = diffuse + specular;
	out_color = vec4(result_color, shadow_depth);
}
