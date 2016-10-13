#version 330 core

uniform sampler2D screen_texture;

in vec2 texture_coord;

out vec3 out_color;


void main()
{
    vec3 chanel_weights = vec3(0.2126, 0.7152, 0.0722);
    vec3 color = texture(screen_texture, texture_coord).rgb;
	out_color = vec3(dot(chanel_weights, color));
}
