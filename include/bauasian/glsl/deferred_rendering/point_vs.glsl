#version 420 core
#include "../bindings.glsl"
#include "../common/lights.glsl"

layout (location = 0) in vec3 vertex_position;

layout (std140, binding = BUFFER_POINT_LIGHT_BINDING) uniform PointLightBuffer
{
    PointLight point_light;
};

layout(std140, binding = BUFFER_CAMERA_BINDING) uniform CameraBuffer
{
    mat4 projection_matrix;
    mat4 view_matrix;
    vec3 position;
	float near;
	float far;
} camera;


void main()
{
    gl_Position = camera.projection_matrix * camera.view_matrix * point_light.model_matrix * vec4(vertex_position, 1.f);
}
