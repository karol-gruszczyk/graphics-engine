#version 330 core
#include "../common/lights.glsl"

layout(std140) uniform SceneBuffer
{
    DirectionalLight dir_lights[MAX_DIR_LIGHTS];
    PointLight point_lights[MAX_POINT_LIGHTS];
    SpotLight spot_lights[MAX_SPOT_LIGHTS];
    vec3 camera_position;
    int num_dir_lights;
    int num_point_lights;
    int num_spot_lights;
};

layout(std140) uniform Material
{
	vec4 ambient_color;
	vec4 diffuse_color;
	vec4 specular_color;

	int use_ambient_texture;
	int use_diffuse_texture;
	int use_specular_texture;
	int use_normal_texture;
	int use_displacement_texture;
	int use_opacity_texture;

	float shininess;
} material;

uniform sampler2D ambient_texture;
uniform sampler2D diffuse_texture;
uniform sampler2D specular_texture;
uniform sampler2D normal_texture;
uniform sampler2D displacement_texture;
uniform sampler2D opacity_texture;

in vec3 position;
in vec2 texture_coord;
in vec3 normal;
in mat3 tbn;
in vec3 tangent_position;
in vec3 tangent_camera_position;

layout (location = 0) out vec3 out_albedo;
layout (location = 1) out vec3 out_specular;
layout (location = 2) out vec3 out_normal;
layout (location = 3) out vec3 out_position;

vec3 fragment_ambient_color;
vec3 fragment_diffuse_color;
vec3 fragment_specular_color;
vec3 fragment_normal;

void setFragmentColors();
vec2 getParallaxTextureCoords();


void main()
{
    out_position = position;
    setFragmentColors();
}

void setFragmentColors()
{
    vec2 corrected_texture_coord;
    // displacement
    if (material.use_displacement_texture == 1)
        corrected_texture_coord = getParallaxTextureCoords();
    else
        corrected_texture_coord = texture_coord;

    // opacity
    if (material.use_opacity_texture == 1)
    {
        float opacity = texture(opacity_texture, corrected_texture_coord).r;
        if (opacity < MIN_ALPHA_DISCARD)
            discard;
    }

    // ambient
	if (material.use_ambient_texture == 1)
		fragment_ambient_color = texture2D(ambient_texture, corrected_texture_coord).rgb;
	else
	    fragment_ambient_color = material.ambient_color.rgb;

    // diffuse
	if (material.use_diffuse_texture == 1)
		out_albedo = texture2D(diffuse_texture, corrected_texture_coord).rgb;
	else
	    out_albedo = material.diffuse_color.rgb;

	// specular
    if (material.use_specular_texture == 1)
		out_specular = vec3(texture2D(specular_texture, corrected_texture_coord).r);
	else
	    out_specular = material.specular_color.rgb;

    // normal
	if (material.use_normal_texture == 1)
		out_normal = normalize(tbn * (texture2D(normal_texture, corrected_texture_coord).rgb * 2.f - 1.f));
	else
	    out_normal = normal;
}

vec2 getParallaxTextureCoords()
{
    const float min_layers = 8;
    const float max_layers = 16;
    const float height_scale = 0.1f;

	vec3 view_dir = normalize(tangent_camera_position - tangent_position);
    float num_layers = mix(max_layers, min_layers, abs(dot(vec3(0.f, 0.f, 1.f), view_dir)));
    float layer_depth = 1.f / num_layers;
    float current_layer_depth = 0.f;

    vec2 p = view_dir.xy * height_scale;
    vec2 delta_texture_coord = p / num_layers;
    vec2 current_texture_coord = texture_coord;
    float previous_depth_map_value;
    float current_depth_map_value = texture(displacement_texture, current_texture_coord).r;
    while (current_layer_depth < current_depth_map_value)
    {
        current_texture_coord -= delta_texture_coord;
        previous_depth_map_value = current_depth_map_value;
        current_depth_map_value = texture(displacement_texture, current_texture_coord).r;
        current_layer_depth += layer_depth;
    }

    vec2 previous_texture_coord = current_texture_coord + delta_texture_coord;

    float before_depth = previous_depth_map_value - current_layer_depth + layer_depth;
    float after_depth = current_depth_map_value - current_layer_depth;

    float weight = after_depth / (after_depth - before_depth);
    return previous_texture_coord * weight + current_texture_coord * (1.f - weight);
}
