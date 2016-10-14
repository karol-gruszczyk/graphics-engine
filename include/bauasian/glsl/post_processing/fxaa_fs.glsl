#version 330 core

#define FXAA_SPAN_MAX 16.f
#define FXAA_REDUCE_MUL 1.f / 8.f
#define FXAA_REDUCE_MIN 1.f / 128.f

uniform sampler2D screen_texture;
uniform vec2 pixel_size;

in vec2 texture_coord;

out vec3 out_color;


void main()
{
    vec3 lum = vec3(0.2126, 0.7152, 0.0722);

    float m_lum = dot(lum, texture(screen_texture, texture_coord).rgb);
    float tl_lum = dot(lum, texture(screen_texture, texture_coord + vec2(-pixel_size.x, pixel_size.y)).rgb);
    float tr_lum = dot(lum, texture(screen_texture, texture_coord + pixel_size).rgb);
    float bl_lum = dot(lum, texture(screen_texture, texture_coord - pixel_size).rgb);
    float br_lum = dot(lum, texture(screen_texture, texture_coord + vec2(pixel_size.x, -pixel_size.y)).rgb);

    float min_lum = min(m_lum, min(min(tl_lum, tr_lum), min(bl_lum, br_lum)));
    float max_lum = max(m_lum, max(max(tl_lum, tr_lum), max(bl_lum, br_lum)));

    vec2 direction;
    direction.x = ((tl_lum + tr_lum) - (bl_lum + br_lum));
    direction.y = ((tl_lum + bl_lum) - (tr_lum + br_lum));

    float reduce = max((tl_lum + tr_lum + bl_lum + br_lum) * 0.25f * FXAA_REDUCE_MUL, FXAA_REDUCE_MIN);
    float adjust = 1.f / (min(abs(direction.x), abs(direction.y)) + reduce);

    direction = clamp(direction * adjust, vec2(-FXAA_SPAN_MAX), vec2(FXAA_SPAN_MAX)) * pixel_size;

    vec3 rgb_a = 0.5f * (texture(screen_texture, texture_coord - direction * 1.f / 3.f).rgb +
                        texture(screen_texture, texture_coord + direction * 1.f / 3.f).rgb);
    vec3 rgb_b = rgb_a * 0.5f + 0.25f * (texture(screen_texture, texture_coord - direction * 0.5f).rgb +
                                         texture(screen_texture, texture_coord + direction * 0.5f).rgb);
    float lum_b = dot(rgb_b, lum);
    if (lum_b < min_lum || lum_b > max_lum)
        out_color = rgb_a;
    else
        out_color = rgb_b;
}
