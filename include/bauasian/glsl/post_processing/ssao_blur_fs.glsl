#version 420 core
#include "../bindings.glsl"

#define BLUR_SIZE 4

layout (binding = DEFERRED_SSAO_BINDING) uniform sampler2D ssao_texture;

uniform vec2 pixel_size;

in vec2 texture_coord;

layout (location = 0) out float out_color;


void main()
{
    float result = 0.f;
    for (int i = 0; i < BLUR_SIZE; ++i)
    {
        for (int j = 0; j < BLUR_SIZE; ++j)
        {
            result += texture(ssao_texture, texture_coord + (vec2(float(i), float(j)) - 2.f) * pixel_size).r;
        }
    }
    out_color = result / (BLUR_SIZE * BLUR_SIZE);
}
