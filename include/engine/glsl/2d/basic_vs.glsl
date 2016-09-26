#version 330

layout(location = 0) in vec2 vertex_position;
layout(location = 1) in vec2 vertex_texture_coord;

out vec2 texture_coord;

uniform mat4 projection_matrix;
uniform mat4 model_matrix;


void main()
{
	texture_coord = vertex_texture_coord;
	gl_Position = projection_matrix * model_matrix * vec4(vertex_position, 0.f, 1.f);
}
