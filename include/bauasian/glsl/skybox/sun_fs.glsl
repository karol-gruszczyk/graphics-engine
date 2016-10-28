#version 330 core
#include "../utils/pi.glsl"
#include "../utils/random.glsl"

uniform vec3 light_direction;

in vec3 position;

out vec3 out_color;

const int   num_samples = 3;
const vec3  Wavelength = vec3(0.650, 0.570, 0.475);

const vec3  wave_length = 1.0f / pow(Wavelength, vec3(4.0f));

const float inner_radius = 10.0;
const float outer_radius = inner_radius * 1.05;
const float inner_radius2 = inner_radius * inner_radius;
const float outer_radius2 = outer_radius * outer_radius;
const float length_scale = 1.0 / (outer_radius - inner_radius);
const float scale_depth = 0.25;
const float scale_over_scale_depth = length_scale / scale_depth;
const vec3  camera_position = vec3(0.0, inner_radius - 0.24f, 0.0);
const float camera_height = length(camera_position);
const float fCameraHeight2 = camera_height * camera_height;

const float m_e_sun  = 20.0;
const float m_kr = 0.0015;
const float m_km = 0.0025;
const float kr_e_sun = 0.0015 * m_e_sun;
const float km_e_sun = 0.0025 * m_e_sun;
const float kr_4PI = m_kr * 4 * PI;
const float km_4PI = m_km * 4 * PI;

const float sun_brightness = 1000.f;
const vec3 sun_color = vec3(1.f, 1.f, 0.7f);

const float mie_distribution =  -0.991f;


float phase(float alpha, float g)
{
    float g2 = g * g;
    float a = 3.f * (1.f - g2);
    float b = 2.f * (2.f + g2);
    float c = 1.f + alpha * alpha;
    float d = pow(1.f + g2 - 2.f * g * alpha, 1.5f);
    return (a / b) * (c / d);
}

float scale(float f_cos)
{
   float x = 1.0 - f_cos;
   return scale_depth * exp(-0.00287 + x * (0.459 + x * (3.83 + x * (-6.80 + x * 5.25))));
}

void main()
{
    float cos_angle = dot(normalize(position), light_direction);
    vec3 sun = sun_color * sun_brightness;
    sun *= cos_angle < -0.998f ? vec3(1.f) : vec3(0.f);

    // Get the ray from the camera to the vertex and its length (which
    // is the far point of the ray passing through the atmosphere)
    vec3 pos = normalize(position) * outer_radius;
    vec3 ray = normalize(position);
    float far = length(ray);
    ray /= far;

    // Calculate the ray's starting position, then calculate its scattering offset
    vec3 start = camera_position;
    float height = length(start);
    float depth = exp(scale_over_scale_depth * (inner_radius - camera_height));
    float start_angle = dot(ray, start) / height;
    float start_offset = depth * scale(start_angle);

    // Initialize the scattering loop variables

    float sample_length = far / float(num_samples);
    float scaled_length = sample_length * length_scale;
    vec3 sample_ray = ray * sample_length;
    vec3 sample_point = start + sample_ray * 0.5;

    // Now loop through the sample rays
    vec3 scatter_color = vec3(0.f);
    for(int i = 0; i < num_samples; i++)
    {
        float height = length(sample_point);
        float depth = exp(scale_over_scale_depth * (inner_radius - height));
        float light_angle = dot(-light_direction, sample_point) / height;
        float camera_angle = dot(ray, sample_point) / height;
        float scatter_strength = (start_offset + depth * (scale(light_angle) - scale(camera_angle)));
        vec3 attenuate = exp(-scatter_strength * (wave_length * kr_4PI + km_4PI));
        scatter_color += attenuate * (depth * scaled_length);
        sample_point += sample_ray;
    }

    float mie_phase = phase(cos_angle, mie_distribution);

    vec3 rayleigh_color = scatter_color * (wave_length * kr_e_sun);
    vec3 mie_color = scatter_color * km_e_sun;

    out_color = vec3(0.f);
    out_color += mie_color * mie_phase;
    out_color += rayleigh_color;
    out_color += sun * mie_color;
    out_color = max(vec3(0.f), out_color);
}
