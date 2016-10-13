#version 330 core

uniform sampler2D screen_texture;
uniform vec3 color_weight;

in vec2 texture_coord;

out vec3 out_color;


void main()
{
    vec3 color = texture(screen_texture, texture_coord).rgb;
    float average = dot(color_weight, color);
	out_color = vec3(average);
}
