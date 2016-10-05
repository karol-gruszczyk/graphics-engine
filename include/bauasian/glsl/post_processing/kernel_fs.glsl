#version 330

in vec2 texture_coord;

out vec4 out_color;

uniform sampler2D screen_texture;
uniform mat3 kernel_matrix;
uniform vec2 pixel_size;


void main()
{
    vec3 final_color = vec3(0.f);
    vec2 current_offset = vec2(-pixel_size.x, pixel_size.y);
    for (int i = 0; i < 3; i++)
    {
        current_offset.x = -pixel_size.x;
        for (int j = 0; j < 3; j++)
        {
            current_offset.x += pixel_size.x;
            vec3 sampledColor = vec3(texture(screen_texture, texture_coord + current_offset));
            final_color += sampledColor * kernel_matrix[i][j];
        }
        current_offset.y -= pixel_size.y;
    }

	out_color = vec4(final_color, 1.f);
}
