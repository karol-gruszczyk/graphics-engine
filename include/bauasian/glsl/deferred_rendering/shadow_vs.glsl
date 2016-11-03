#version 420 core
#include "../bindings.glsl"

layout (location = 0) in vec3 vertex_position;

layout (std140, binding = BUFFER_SHADOW_CAMERA_BINDING) uniform CameraBuffer
{
    mat4 projection_matrix;
    mat4 view_matrix;
    vec3 position;
	float near;
	float far;
} camera;

layout(std140, binding = BUFFER_MATRICES_BINDING) uniform MatricesBuffer
{
    mat4 model_matrix;
    mat4 normal_matrix;
};


void main()
{
    gl_Position = camera.projection_matrix * camera.view_matrix * model_matrix * vec4(vertex_position, 1.f);
}
