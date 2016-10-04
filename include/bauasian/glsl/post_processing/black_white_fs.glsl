#version 330

in vec2 texture_coord;

out vec4 out_color;

uniform sampler2D screen_texture;
uniform vec3 color_weight;


void main()
{
    vec3 color = vec3(texture(screen_texture, texture_coord));
    float average = color_weight.r * color.r + color_weight.g * color.g + color_weight.b * color.b;
	out_color = vec4(vec3(average), 1.f);
}
