#version 330 core

uniform sampler2D font_texture;
uniform vec3 text_color;

in vec2 texture_coord;

out vec4 out_color;


void main()
{
    float alpha = texture(font_texture, texture_coord).r;
    out_color = vec4(text_color, alpha);
}
