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

const int   nSamples = 3;
const float fSamples = 3.0;
const vec3  Wavelength = vec3(0.650, 0.570, 0.475);

const vec3  v3InvWavelength = 1.0f / pow(Wavelength, vec3(4.0f));

const float fInnerRadius = 10.0;
const float fOuterRadius = 100.0;
const float fInnerRadius2 = fInnerRadius * fInnerRadius;
const float fOuterRadius2 = fOuterRadius * fOuterRadius;
const float fScale = 1.0 / (fOuterRadius - fInnerRadius);
const float fScaleDepth = 0.25;
const float fScaleOverScaleDepth = fScale / fScaleDepth;
const vec3  v3CameraPos = vec3(0.0, fInnerRadius * 1.015, 0.0);
const float fCameraHeight = length(v3CameraPos);
const float fCameraHeight2 = fCameraHeight * fCameraHeight;

const float PI = 3.141592653;
const float fm_ESun  = 20.0;
const float fm_Kr    = 0.0015;
const float fm_Km    = 0.0025;
const float fKrESun = fm_Kr * fm_ESun;
const float fKmESun = fm_Km * fm_ESun;
const float fKr4PI = fm_Kr * 4 * PI;
const float fKm4PI = fm_Km * 4 * PI;

const float sun_size = 20.f;
const float sun_brightness = 1000.f;
const vec3 sun_color = vec3(1.f, 1.f, 0.5f);

const float mie_distribution =  -0.991f;
const float mie_brightness = 1.f;

const vec3 sunset_color = vec3(1.f, 0.f, 0.f);

float scale(float fCos)
{
   float x = 1.0 - fCos;
   return fScaleDepth * exp(-0.00287 + x * (0.459 + x * (3.83 + x * (-6.80 + x * 5.25))));
}

void main()
{
    float cos_angle = dot(normalize(position), light_direction);
    float mie_phase = phase(cos_angle, mie_distribution) * mie_brightness;
    vec3 sun = sun_color * sun_brightness;
    sun *= cos_angle < -0.998f ? vec3(1.f) : vec3(0.f);

    // Get the ray from the camera to the vertex and its length (which
    // is the far point of the ray passing through the atmosphere)
    vec3 v3Pos = normalize(position) * fOuterRadius;
    vec3 v3Ray = v3Pos - v3CameraPos;
    float fFar = length(v3Ray);
    v3Ray /= fFar;

    // Calculate the ray's starting position, then calculate its scattering offset
    vec3 v3Start = v3CameraPos;
    float fHeight = length(v3Start);
    float fDepth = exp(fScaleOverScaleDepth * (fInnerRadius - fCameraHeight));
    float fStartAngle = dot(v3Ray, v3Start) / fHeight;
    float fStartOffset = fDepth * scale(fStartAngle);

    // Initialize the scattering loop variables

    float fSampleLength = fFar / fSamples;
    float fScaledLength = fSampleLength * fScale;
    vec3 v3SampleRay = v3Ray * fSampleLength;
    vec3 v3SamplePoint = v3Start + v3SampleRay * 0.5;

    // Now loop through the sample rays
    vec3 v3FrontColor = vec3(0.f);
    for(int i = 0; i < nSamples; i++)
    {
        float fHeight = length(v3SamplePoint);
        float fDepth = exp(fScaleOverScaleDepth * (fInnerRadius - fHeight));
        float fLightAngle = dot(-light_direction, v3SamplePoint) / fHeight;
        float fCameraAngle = dot(v3Ray, v3SamplePoint) / fHeight;
        float fScatter = (fStartOffset + fDepth * (scale(fLightAngle) - scale(fCameraAngle)));
        vec3 v3Attenuate = exp(-fScatter * (v3InvWavelength * fKr4PI + fKm4PI));
        v3FrontColor += v3Attenuate * (fDepth * fScaledLength);
        v3SamplePoint += v3SampleRay;
    }

    float vert_sunset = dot(light_direction, normalize(vec3(light_direction.x, 0.f, light_direction.z)));
    float sunset = smoothstep(0.9f, 1.f, vert_sunset);
    float sunset_halo = sunset * phase(cos_angle, -0.99995);
    float hori_sunset = smoothstep(0.8f, 1.f, dot(normalize(position), -light_direction));

    v3FrontColor += sunset_color * (hori_sunset * sunset);

    vec3 rayleigh_color = v3FrontColor * (v3InvWavelength * fKrESun);
    vec3 mie_color = v3FrontColor * fKmESun;

    out_color = vec3(0.f);
    out_color += mie_color * mie_phase * sun_color;
    out_color += rayleigh_color;
    out_color += sun * mie_color;
}
