#version 330 core

#define NITROGEN_ABSORPTION vec3(0.18867780436772762, 0.4978442963618773, 0.6616065586417131)

uniform vec3 light_direction;

in vec3 position;

out vec3 out_color;


float phase(float alpha, float g)
{
    float g2 = g * g;
    float a = 3.f * (1.f - g2);
    float b = 2.f * (2.f + g2);
    float c = 1.f + alpha * alpha;
    float d = pow(1.f + g2 - 2.f * g * alpha, 1.5f);
    return (a / b) * (c / d);
}

float atmospheric_depth(vec3 position, vec3 dir)
{
    float a = dot(dir, dir);
    float b = 2.f * dot(dir, position);
    float c = dot(position, position) - 1.f;
    float det = b * b - 4.f * a * c;
    float detSqrt = sqrt(det);
    float q = (-b - detSqrt) / 2.f;
    float t1 = c / q;
    return t1;
}

vec3 absorb(float distance, vec3 color, float factor)
{
    return color - color * pow(NITROGEN_ABSORPTION, vec3(factor / distance));
}

void main()
{
    float sun_size = 1.f;
    float sun_brightness = 1.f;
    vec3 sun_color = vec3(1.f);
    float surface_height = 0.2f;
    float step_count = 10.f;
    float scatter_strength = 8.f;
    float rayleigh_distribution = 0.05f;
    float rayleigh_brightness = 1.f;
    float rayleigh_scatter_strength = 8.f;
    float rayleight_collection_power = 0.f;
    float mie_distribution = 0.05f;
    float mie_brightness = 1.f;
    float mie_scatter_strength = 0.4f;
    float mie_collection_power = 1.0f;

    vec3 eye_direction = normalize(position);
    vec3 eye_position = vec3(0.f, surface_height, 0.f);
    float cos_angle = dot(eye_direction, -light_direction);

    float rayleigh_factor = phase(cos_angle, rayleigh_distribution) * rayleigh_brightness;
    float mie_factor = phase(cos_angle, mie_distribution) * mie_brightness;
    vec3 sun = smoothstep(0.0, 15.f / sun_size * sqrt(sun_brightness), phase(cos_angle, 0.9995)) * sun_brightness * sun_color;

    float eye_extinction = clamp(dot(eye_direction, vec3(0.f, 1.f, 0.f)) * 5.f + 1.f, 0.f, 1.f);

    float eye_depth = atmospheric_depth(eye_position, eye_direction);
    float step_length = eye_depth / step_count;

    vec3 rayleigh_collected = vec3(0.f);
    vec3 mie_collected = vec3(0.f);
    for (float i = 0.f; i < step_count; i += 1.f)
    {
        float sample_distance = step_length * i;
        vec3 sample_position = eye_position + eye_direction * sample_distance;
        float sample_depth = atmospheric_depth(sample_position, eye_direction);
        float extinction = clamp(dot(eye_direction, -light_direction) / 2.f + 0.7f, 0.f, 1.f);
        vec3 influx = absorb(sample_depth, sun_color, scatter_strength) * extinction;
        rayleigh_collected += absorb(sample_depth, NITROGEN_ABSORPTION * influx, rayleigh_scatter_strength);
        mie_collected += absorb(sample_depth, influx, mie_scatter_strength);
    }

    rayleigh_collected = eye_extinction * rayleigh_collected * pow(eye_depth, rayleight_collection_power) / step_count;
    mie_collected = eye_extinction * mie_collected * pow(eye_depth, mie_collection_power) / step_count;

    vec3 color = vec3(0.f);
    color += rayleigh_factor * rayleigh_collected;
    color += mie_factor * mie_collected;
    color += sun * mie_collected;

    out_color = color;
}
