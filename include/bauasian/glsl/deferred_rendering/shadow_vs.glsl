#version 420 core
#include "../uniform_buffers/shadow_buffer.glsl"
#include "../uniform_buffers/matrices_buffer.glsl"

layout (location = 0) in vec3 vertex_position;


void main()
{
    gl_Position = shadow.light_space_matrix * model_matrix * vec4(vertex_position, 1.f);
}
