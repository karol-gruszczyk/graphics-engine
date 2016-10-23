#version 330 core

layout (location = 0) in vec3 vertex_position;

uniform mat4 model_matrix;
uniform mat4 projection_view_matrix;

out vec2 texture_coord;


void main()
{
    gl_Position = projection_view_matrix * model_matrix * vec4(vertex_position, 1.f);
    texture_coord = gl_Position.xy / gl_Position.w / 2.f + 0.5f;
}
