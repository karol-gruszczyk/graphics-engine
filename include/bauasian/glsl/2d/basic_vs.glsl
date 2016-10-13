#version 330 core

layout(location = 0) in vec4 vertex;

uniform mat4 projection_matrix;
uniform mat4 model_matrix;

out vec2 texture_coord;


void main()
{
	texture_coord = vertex.zw;
	gl_Position = projection_matrix * model_matrix * vec4(vertex.xy, 0.f, 1.f);
}
