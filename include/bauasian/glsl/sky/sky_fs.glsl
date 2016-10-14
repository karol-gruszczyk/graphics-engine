#version 330 core

in vec3 position;

out vec3 out_color;


void main()
{
    float angle = dot(normalize(position), vec3(0.f, 1.f, 0.f));
    out_color = vec3(0.f, 0.f, angle);
}
