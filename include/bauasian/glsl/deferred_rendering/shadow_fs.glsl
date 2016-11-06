#version 330 core

out vec2 out_color;


void main()
{
    float depth = gl_FragCoord.z;

    float dx = dFdx(depth);
    float dy = dFdy(depth);
    float depth_2 = depth * depth + 0.25f * (dx * dx + dy * dy);

    out_color = vec2(depth, depth_2);
}
