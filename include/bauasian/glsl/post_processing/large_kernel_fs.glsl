#version 330

in vec2 texture_coord;

out vec4 out_color;

uniform sampler2D screen_texture;
uniform float kernel_matrix[25];
uniform vec2 offset;


void main()
{
    vec3 final_color = vec3(0.f);
    vec2 current_offset = vec2(2 * -offset.x, 2 * offset.y);
    for (int i = 0; i < 5; i++)
    {
        current_offset.x = 2 * -offset.x;
        for (int j = 0; j < 5; j++)
        {
            current_offset.x += offset.x;
            vec3 sampledColor = vec3(texture(screen_texture, texture_coord + current_offset));
            final_color += sampledColor * kernel_matrix[i * 5 + j];
        }
        current_offset.y -= offset.y;
    }

	out_color = vec4(final_color, 1.f);
}
