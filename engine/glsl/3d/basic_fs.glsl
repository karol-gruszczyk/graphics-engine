#version 330

in vec3 position;
in vec2 texture_coord;
in vec3 normal;

out vec4 out_color;

uniform sampler2D diffuse_texture;


void main()
{
	out_color = texture2D(diffuse_texture, texture_coord);
}
