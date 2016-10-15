#version 330 core

uniform samplerCube cube_texture;

in vec3 position;

out vec4 out_color;


void main()
{
	out_color = texture(cube_texture, -position);
}
