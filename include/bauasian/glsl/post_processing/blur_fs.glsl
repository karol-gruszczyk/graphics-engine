#version 330 core

in vec2 texture_coord;

out vec4 out_color;

uniform sampler2D screen_texture;
uniform vec2 pixel_size;
uniform uint radius;


void main()
{
    vec3 color = texture(screen_texture, texture_coord).rgb;
    vec2 current_offset = pixel_size;
    for (uint i = uint(0); i < radius; i++)
    {
        color += texture(screen_texture, texture_coord + vec2(current_offset.x, 0.f)).rgb;
        color += texture(screen_texture, texture_coord + vec2(-current_offset.x, 0.f)).rgb;
        color += texture(screen_texture, texture_coord + vec2(0.f, current_offset.y)).rgb;
        color += texture(screen_texture, texture_coord + vec2(0.f, -current_offset.y)).rgb;
        current_offset += pixel_size;
    }
    color /= radius * 4.f + 1;
    out_color = vec4(color, 1.f);
}