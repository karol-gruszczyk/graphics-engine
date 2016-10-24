#version 330 core

layout (location = 0) in vec4 vertex;

out vec2 texture_coord;


void main()
{
    texture_coord = vertex.zw;
    gl_Position = vec4(vertex.xy, 1.f, 1.f);
}
