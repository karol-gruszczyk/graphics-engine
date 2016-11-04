#version 420 core
#include "../uniform_buffers/camera_buffer.glsl"
#include "../uniform_buffers/spot_light_buffer.glsl"

layout (location = 0) in vec3 vertex_position;


void main()
{
    gl_Position = camera.projection_matrix * camera.view_matrix * spot_light.model_matrix * vec4(vertex_position, 1.f);
}
