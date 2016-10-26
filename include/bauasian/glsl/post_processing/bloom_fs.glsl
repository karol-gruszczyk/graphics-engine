#version 330 core
#include "../common/luminance.glsl"

uniform sampler2D screen_texture;

in vec2 texture_coord;

out vec4 out_color;


void main()
{
    vec3 color = texture(screen_texture, texture_coord).rgb;
    float luma = luminance(color);

    if (luma > 1.f)
        out_color = vec4(color, 1.f);
    else
        out_color = vec4(0.f);
}