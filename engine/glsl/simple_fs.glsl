#version 330

in vec3 position;
in vec2 texture_coord;

out vec4 out_color;

void main()
{
	out_color = vec4(vec3(texture_coord, 1.f) / 2.f + abs(sin(position * 100.f)) / 2.f, 1.f);
}
