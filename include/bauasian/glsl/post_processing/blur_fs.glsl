#version 330

in vec2 texture_coord;

out vec4 out_color;

uniform sampler2D screen_texture;
uniform vec2 pixel_size;
uniform uint radius;


void main()
{
    vec3 color = vec3(texture(screen_texture, texture_coord));
    vec2 current_offset = pixel_size;
    for (uint i = uint(0); i < radius; i++)
    {
        color += vec3(texture(screen_texture, texture_coord + vec2(current_offset.x, 0.f)));
        color += vec3(texture(screen_texture, texture_coord + vec2(-current_offset.x, 0.f)));
        color += vec3(texture(screen_texture, texture_coord + vec2(0.f, current_offset.y)));
        color += vec3(texture(screen_texture, texture_coord + vec2(0.f, -current_offset.y)));
        current_offset += pixel_size;
    }
    color /= radius * 4.f + 1;
    out_color = vec4(color, 1.f);
}