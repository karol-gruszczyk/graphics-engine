#include "../globals.glsl"


vec3 processAmbientLight(vec3 light_color)
{
	return AMBIENT_STRENGTH * light_color;
}

vec3 processDiffuseLight(vec3 normal, vec3 light_ray_direction, vec3 light_color)
{
	return max(dot(normal, light_ray_direction), 0.f) * light_color;
}

vec3 processSpecularLight(vec3 normal, vec3 light_ray_direction, vec3 light_color, vec3 view_dir, float shininess)
{
	vec3 halfway_dir = normalize(light_ray_direction + view_dir);
	return pow(max(dot(halfway_dir, normal), 0.0), shininess) * light_color;
}
