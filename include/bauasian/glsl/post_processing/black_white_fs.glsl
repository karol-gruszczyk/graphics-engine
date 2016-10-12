#version 330 core

in vec2 texture_coord;

out vec3 out_color;

uniform sampler2D screen_texture;
uniform vec3 color_weight;


void main()
{
    vec3 color = texture(screen_texture, texture_coord).rgb;
    float average = dot(color_weight, color);
	out_color = vec3(average);
}
