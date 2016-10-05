#version 330

layout(location = 0) in vec4 vertex;

out vec2 texture_coord;


void main()
{
	texture_coord = vertex.zw;
	gl_Position = vec4(vertex.xy, 0.f, 1.f);
}
