#version 330 core

layout(location = 0) in vec4 vertex;

layout(std140) uniform ModelMatrices
{
    mat4 projection_matrix;
    mat4 view_matrix;
    mat4 model_matrix;
    mat4 normal_matrix;
};

out vec2 texture_coord;
flat out mat3 view_normal_matrix;


void main()
{
	texture_coord = vertex.zw;
	view_normal_matrix = transpose(inverse(mat3(view_matrix)));
	gl_Position = vec4(vertex.xy, 0.f, 1.f);
}
