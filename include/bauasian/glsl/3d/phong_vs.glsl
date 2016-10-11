#version 330 core

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_normal;
layout(location = 2) in vec2 vertex_texture_coord;
layout(location = 3) in vec3 vertex_tangent;
layout(location = 4) in vec3 vertex_bi_tangent;

layout(std140) uniform ModelMatrices
{
    mat4 projection_view_model_matrix;
    mat4 model_matrix;
    mat4 normal_matrix;
};

out vec3 position;
out vec2 texture_coord;
out vec3 normal;
out mat3 tbn;


void main()
{
	position = vec3(model_matrix * vec4(vertex_position, 1.f));
	texture_coord = vertex_texture_coord;
	normal = normalize(mat3(normal_matrix) * vertex_normal);
	gl_Position = projection_view_model_matrix * vec4(vertex_position, 1.f);

    tbn = mat3(normal_matrix) * mat3(vertex_tangent, vertex_bi_tangent, vertex_normal);
}
