#version 420 core
#include "../uniform_buffers/camera_buffer.glsl"

layout(location = 0) in vec4 vertex;

out vec2 texture_coord;
flat out mat3 view_normal_matrix;


void main()
{
	texture_coord = vertex.zw;
	view_normal_matrix = transpose(inverse(mat3(camera.view_matrix)));
	gl_Position = vec4(vertex.xy, 0.f, 1.f);
}
