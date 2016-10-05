#version 330

in vec2 texture_coord;

out vec3 out_color;

uniform sampler2D screen_texture;
uniform vec3 color_weight;


void main()
{
    vec3 color = vec3(texture(screen_texture, texture_coord));
    float average = dot(color_weight, color);
	out_color = vec3(average);
}
