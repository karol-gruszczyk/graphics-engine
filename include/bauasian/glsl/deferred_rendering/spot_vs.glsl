#version 330 core
#include "../common/lights.glsl"

layout (location = 0) in vec3 vertex_position;

layout (std140) uniform SpotLightBuffer
{
    SpotLight spot_light;
};

uniform mat4 model_matrix;
uniform mat4 projection_view_matrix;


void main()
{
    gl_Position = projection_view_matrix * spot_light.model_matrix * vec4(vertex_position, 1.f);
}
