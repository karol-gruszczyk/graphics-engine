#version 330 core

uniform sampler2D depth_texture;

in vec2 texture_coord;

out vec3 out_color;


void main()
{
    float depth = texture(screen_texture, texture_coord).r;

    out_color = vec3(depth);
}
