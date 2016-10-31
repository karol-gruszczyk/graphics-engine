float linearizeDepth(float depth, float near, float far)
{
    float z = depth * 2.f - 1.f; // back to NDC
    return (2.f * near) / (far + near - z * (far - near));
}
