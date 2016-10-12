#version 330 core

layout(location = 0) in vec3 vertex_position;

uniform mat4 projection_view_matrix;


void main()
{
	gl_Position = projection_view_matrix * vec4(vertex_position, 1.f);
}
