#version 420 core
#include "../uniform_buffers/camera_buffer.glsl"

#define MAX_KERNEL_SIZE 64

layout (binding = DEFERRED_NORMAL_BINDING) uniform sampler2D normal_buffer;
layout (binding = DEFERRED_POSITION_BINDING) uniform sampler2D position_buffer;
layout (binding = DEFERRED_SSAO_NOISE_BINDING) uniform sampler2D noise_buffer;

uniform vec3 kernel[MAX_KERNEL_SIZE];
uniform int kernel_size = 16;
uniform float ssao_radius = 100.f;
uniform float ssao_power = 5.f;
uniform vec2 noise_scale;

in vec2 texture_coord;
flat in mat3 view_normal_matrix;

layout (location = 0) out float out_color;


void main()
{
    vec3 position = texture(position_buffer, texture_coord).xyz;
    position = vec3(camera.view_matrix * vec4(position, 1.f));

    vec3 normal = texture(normal_buffer, texture_coord).xyz;
    normal = normalize(view_normal_matrix * normal);
    vec3 random_vec = texture(noise_buffer, texture_coord * noise_scale).xyz;

    vec3 tangent = normalize(random_vec - normal * dot(random_vec, normal));
    vec3 bitangent = cross(normal, tangent);
    mat3 TBN = mat3(tangent, bitangent, normal);

    float occlusion = 0.f;
    for (int i = 0; i < kernel_size; ++i)
    {
        vec3 kernel_position = TBN * kernel[i];
        vec3 sample_position = position + kernel_position * ssao_radius;

        vec4 offset = camera.projection_matrix * vec4(sample_position, 1.f);
        offset.xyz /= offset.w;  // perspective division
        offset.xyz = offset.xyz / 2.f + 0.5f;

        float sample_depth = -texture(position_buffer, offset.xy).w;
        float range_check = smoothstep(0.f, 1.f, ssao_radius / abs(position.z - sample_depth));
        occlusion += (sample_depth >= sample_position.z ? 1.f : 0.f) * range_check;
    }
    occlusion = 1.f - occlusion / kernel_size;
    out_color = pow(occlusion, ssao_power);
}
