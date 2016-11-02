#version 420 core
#include "../bindings.glsl"

layout(location = 0) in vec4 vertex;

layout(std140, binding = BUFFER_CAMERA_BINDING) uniform CameraBuffer
{
    mat4 projection_matrix;
    mat4 view_matrix;
    vec3 position;
	float near;
	float far;
} camera;

out vec2 texture_coord;
flat out mat3 view_normal_matrix;


void main()
{
	texture_coord = vertex.zw;
	view_normal_matrix = transpose(inverse(mat3(camera.view_matrix)));
	gl_Position = vec4(vertex.xy, 0.f, 1.f);
}
