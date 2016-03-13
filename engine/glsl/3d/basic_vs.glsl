#version 330

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec2 vertex_texture_coord;
layout(location = 2) in vec3 vertex_normal;

out vec3 position;
out vec2 texture_coord;
out vec3 normal;

uniform mat4 projection_matrix;
uniform mat4 view_matrix;
uniform mat4 model_matrix;


void main()
{
	position = vertex_position;
	texture_coord = vertex_texture_coord;
	normal = vertex_normal;
	gl_Position = projection_matrix * view_matrix * model_matrix * vec4(vertex_position, 1.f);
}
