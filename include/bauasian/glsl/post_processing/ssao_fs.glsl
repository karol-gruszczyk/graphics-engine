#version 420 core
#include "../bindings.glsl"
#include "../utils/linearize_depth.glsl"

#define KERNEL_SIZE 64

layout (binding = DEFERRED_NORMAL_BINDING) uniform sampler2D normal_buffer;
layout (binding = DEFERRED_POSITION_BINDING) uniform sampler2D position_buffer;
layout (binding = DEFERRED_SSAO_NOISE_BINDING) uniform sampler2D noise_buffer;

uniform vec3 kernel[KERNEL_SIZE];
uniform float ssao_radius = 0.000001f;
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
    vec3 normal = texture(normal_buffer, texture_coord).xyz;
    vec3 random_vec = normalize(texture(noise_buffer, texture_coord * noise_scale).xyz);

    vec3 tangent = normalize(random_vec - normal * dot(random_vec, normal));
    vec3 bitangent = cross(normal, tangent);
    mat3 TBN = mat3(tangent, bitangent, normal);

    vec3 sampled_position = position;
    vec4 offset = projection_matrix * vec4(sampled_position, 1.f);
    offset.xyz /= offset.w;
    offset.xyz = offset.xyz / 2.f + 0.5f;
    out_color = vec3(texture(position_buffer, texture_coord).w);
    out_color = vec3(offset.xy, 0.f);
}
