#version 330

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec2 vertex_texture_coord;
layout(location = 2) in vec3 vertex_normal;

out vec3 position;
out vec2 texture_coord;
out vec3 normal;

uniform mat4 projection_view_model_matrix;
uniform mat4 model_matrix;
uniform mat3 normal_matrix;


void main()
{
	position = vec3(model_matrix * vec4(vertex_position, 1.f));
	texture_coord = vertex_texture_coord;
	normal = normalize(normal_matrix * vertex_normal);
	gl_Position = projection_view_model_matrix * vec4(vertex_position, 1.f);
}
