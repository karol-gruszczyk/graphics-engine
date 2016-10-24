float getLightAttenuation(float distance, vec3 attenuation)
{
    return 1.f / (attenuation.x + attenuation.y * distance + attenuation.z * distance * distance);
}
