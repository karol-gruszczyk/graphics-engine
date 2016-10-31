#version 420 core
#include "../bindings.glsl"

layout (binding = DEFERRED_SSAO_BINDING) uniform sampler2D ssao_texture;

in vec2 texture_coord;

out vec4 out_color;


void main()
{
    vec3 fragment_ssao = texture(ssao_texture, texture_coord).rgb;
	out_color = vec4(vec3(fragment_ssao.r), 1.f);
}
