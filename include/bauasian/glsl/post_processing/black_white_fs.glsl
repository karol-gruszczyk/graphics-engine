#version 420 core
#include "../utils/luminance.glsl"
#include "../bindings.glsl"

layout (binding = POST_PROCESSING_COLOR_TEXTURE) uniform sampler2D screen_texture;

in vec2 texture_coord;

out vec3 out_color;


void main()
{
    vec3 color = texture(screen_texture, texture_coord).rgb;
	out_color = vec3(luminance(color));
}
