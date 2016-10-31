#version 420 core
#include "../bindings.glsl"
#include "../utils/linearize_depth.glsl"

#define MAX_KERNEL_SIZE 64

layout (binding = DEFERRED_NORMAL_BINDING) uniform sampler2D normal_buffer;
layout (binding = DEFERRED_POSITION_BINDING) uniform sampler2D position_buffer;
layout (binding = DEFERRED_SSAO_NOISE_BINDING) uniform sampler2D noise_buffer;

uniform vec3 kernel[MAX_KERNEL_SIZE];
uniform int kernel_size = 8;
uniform float ssao_radius = 100.f;
uniform vec2 noise_scale;

layout(std140) uniform ModelMatrices
{
    mat4 projection_matrix;
    mat4 view_matrix;
    mat4 model_matrix;
    mat4 normal_matrix;
};

in vec2 texture_coord;

layout (location = 0) out vec3 out_color;


void main()
{
    vec3 position = texture(position_buffer, texture_coord).xyz;
    position = vec3(view_matrix * vec4(position, 1.f));

    vec3 normal = texture(normal_buffer, texture_coord).xyz;
    normal = normalize(transpose(inverse(mat3(view_matrix))) * normal);
    vec3 random_vec = texture(noise_buffer, texture_coord * noise_scale).xyz;

    vec3 tangent = normalize(random_vec - normal * dot(random_vec, normal));
    vec3 bitangent = cross(normal, tangent);
    mat3 TBN = mat3(tangent, bitangent, normal);

    float occlusion = 0.f;
    for (int i = 0; i < kernel_size; ++i)
    {
        vec3 kernel_position = TBN * kernel[i];
        vec3 sample_position = position + kernel_position * ssao_radius;

        vec4 offset = projection_matrix * vec4(sample_position, 1.f);
        offset.xyz /= offset.w;  // perspective division
        offset.xyz = offset.xyz / 2.f + 0.5f;

        float sample_depth = -texture(position_buffer, offset.xy).w;
        float range_check = smoothstep(0.f, 1.f, ssao_radius / abs(position.z - sample_depth));
        occlusion += (sample_depth >= sample_position.z ? 1.f : 0.f) * range_check;
    }
    out_color = vec3(1.f - occlusion / kernel_size);
}
