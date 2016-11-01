#version 330 core
#include "../common/lights.glsl"

layout (location = 0) in vec3 vertex_position;

layout (std140) uniform PointLightBuffer
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
