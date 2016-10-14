#version 400 core

#define FXAA_GREEN_AS_LUMA 1
#define FXAA_PC 1
#define FXAA_GLSL_130 1
#define FXAA_QUALITY__PRESET 12
#include "fxaa/Fxaa3_11.h"

uniform sampler2D screen_texture;
uniform vec2 pixel_size;

in vec2 texture_coord;

out vec3 out_color;


vec3 processFxaa(float subpix, float edge_threshold, float edge_threshold_min)
{
    return FxaaPixelShader(texture_coord,
                           vec4(0.f),  // not used
                           screen_texture,
                           screen_texture, screen_texture,  // not used
                           pixel_size,
                           vec4(0.f), vec4(0.f), vec4(0.f),  // not used
                           subpix, edge_threshold, edge_threshold_min,
                           0.0, 0.0, 0.0, vec4(0.f)  // not used
                           ).rgb;
}

void main()
{
    out_color = processFxaa(0.5, 0.166, 0.0);  // default values, should be changed to uniforms
}
