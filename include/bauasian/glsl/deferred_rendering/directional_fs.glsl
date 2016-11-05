#version 420 core
#include "../uniform_buffers/shadow_buffer.glsl"
#include "../uniform_buffers/camera_buffer.glsl"
#include "../uniform_buffers/dir_light_buffer.glsl"
#include "../common/blinn_phong.glsl"

layout (binding = DEFERRED_ALBEDO_BINDING) uniform sampler2D albedo_buffer;
layout (binding = DEFERRED_SPECULAR_BINDING) uniform sampler2D specular_buffer;
layout (binding = DEFERRED_NORMAL_BINDING) uniform sampler2D normal_buffer;
layout (binding = DEFERRED_POSITION_BINDING) uniform sampler2D position_buffer;
layout (binding = DEFERRED_SHADOW_MAP_BINDING) uniform sampler2DShadow shadow_map;

in vec2 texture_coord;

out vec4 out_color;


float pcf(sampler2DShadow shadow_texture, vec3 projected_position)
{
    float z = projected_position.z;
    float depth = texture(shadow_texture, projected_position.xyz);
    depth += texture(shadow_texture, vec3(projected_position.xy + vec2(shadow.pixel_size), z));
    depth += texture(shadow_texture, vec3(projected_position.xy - vec2(shadow.pixel_size), z));
    depth += texture(shadow_texture, vec3(projected_position.xy + vec2(-shadow.pixel_size, shadow.pixel_size), z));
    depth += texture(shadow_texture, vec3(projected_position.xy + vec2(shadow.pixel_size, -shadow.pixel_size), z));
    return depth / 5.f;
}

void main()
{
    float shadow_depth = 1.f;
    vec3 frag_position = texture(position_buffer, texture_coord).rgb;
    if (dir_light.use_shadow_map == 1)
    {
        vec4 shadow_position = shadow.light_space_matrix * vec4(frag_position, 1.f);
        shadow_position.xyz /= shadow_position.w;
        shadow_position.xyz = shadow_position.xyz * 0.5f + 0.5f;
        shadow_position.z -= shadow.pixel_size;
        shadow_depth = pcf(shadow_map, shadow_position.xyz);
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
	out_color = vec4(result_color, 1.f) * shadow_depth;
}
