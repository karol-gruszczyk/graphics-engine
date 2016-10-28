#version 330 core
#include "../utils/luminance.glsl"

uniform sampler2D screen_texture;
uniform sampler2D bloom_texture;
uniform float exposure;
uniform float gamma;

in vec2 texture_coord;

out vec4 out_color;


void main()
{
    vec3 hdr_color = texture(screen_texture, texture_coord).rgb;
    hdr_color += texture(bloom_texture, texture_coord).rgb;

    // exposure tone mapping
    vec3 color = vec3(1.f) - exp(-hdr_color * exposure);

    // gamma correction
    color = pow(color, vec3(1.f / gamma));

    out_color = vec4(color, luminance(color));
}
