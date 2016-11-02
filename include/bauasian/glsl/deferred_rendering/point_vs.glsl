#version 420 core
#include "../bindings.glsl"
#include "../common/lights.glsl"

layout (location = 0) in vec3 vertex_position;

layout (std140, binding = BUFFER_POINT_LIGHT_BINDING) uniform PointLightBuffer
{
    PointLight point_light;
};

layout(std140) uniform MatricesBuffer
{
    mat4 projection_matrix;
    mat4 view_matrix;
    mat4 model_matrix;
    mat4 normal_matrix;
};


void main()
{
    gl_Position = projection_matrix * view_matrix * point_light.model_matrix * vec4(vertex_position, 1.f);
}
