#version 330 core

uniform sampler2D depth_texture;

in vec2 texture_coord;

out vec3 out_color;


void main()
{
    out_color = texture(depth_texture, texture_coord).rgb;
}
