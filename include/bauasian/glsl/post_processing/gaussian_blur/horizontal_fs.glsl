#version 420 core
#include "../../bindings.glsl"
#include "matrices.glsl"

layout (binding = POST_PROCESSING_COLOR_TEXTURE) uniform sampler2D screen_texture;
uniform vec2 pixel_size;

in vec2 texture_coord;

out vec3 out_color;


void main()
{
    vec3 color = vec3(0.f);
    for (int i = -5; i < 5; i++)
        color += texture(screen_texture, vec2(texture_coord.x + i * pixel_size.x, texture_coord.y)).rgb
            * gaussian_mat11[i + 5];
    out_color = vec3(color);
}
