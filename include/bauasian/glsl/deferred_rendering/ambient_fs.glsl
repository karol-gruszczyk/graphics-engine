#version 420 core
#include "../bindings.glsl"

layout (binding = DEFERRED_ALBEDO_BINDING) uniform sampler2D albedo_buffer;
layout (binding = DEFERRED_SSAO_BINDING) uniform sampler2D ssao_texture;

uniform float occlusion_factor = 0.3f;

in vec2 texture_coord;

out vec4 out_color;


void main()
{
    float fragment_ssao = texture(ssao_texture, texture_coord).r;
	vec3 ambient_color = texture(albedo_buffer, texture_coord).rgb;
	out_color = vec4(occlusion_factor * fragment_ssao * ambient_color, 1.f);
}
