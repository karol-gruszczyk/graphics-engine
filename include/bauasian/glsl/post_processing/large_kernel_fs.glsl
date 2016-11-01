#version 420 core
#include "../bindings.glsl"

layout (binding = POST_PROCESSING_COLOR_TEXTURE) uniform sampler2D screen_texture;

uniform float kernel_matrix[25];
uniform vec2 pixel_size;

in vec2 texture_coord;

out vec3 out_color;


void main()
{
    vec3 final_color = vec3(0.f);
    vec2 current_offset = vec2(2 * -pixel_size.x, 2 * pixel_size.y);
    for (int i = 0; i < 5; i++)
    {
        current_offset.x = 2 * -pixel_size.x;
        for (int j = 0; j < 5; j++)
        {
            current_offset.x += pixel_size.x;
            vec3 sampledColor = texture(screen_texture, texture_coord + current_offset).rgb;
            final_color += sampledColor * kernel_matrix[i * 5 + j];
        }
        current_offset.y -= pixel_size.y;
    }

	out_color = vec3(final_color);
}
