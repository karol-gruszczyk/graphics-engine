#version 330 core
#include "../common/lights.glsl"

layout (location = 0) in vec3 vertex_position;

layout (std140) uniform PointLightBuffer
{
    PointLight point_light;
};

uniform mat4 model_matrix;
uniform mat4 projection_view_matrix;

out vec2 texture_coord;


void main()
{
    gl_Position = projection_view_matrix * point_light.model_matrix * vec4(vertex_position, 1.f);
    texture_coord = gl_Position.xy / gl_Position.w / 2.f + 0.5f;
}
