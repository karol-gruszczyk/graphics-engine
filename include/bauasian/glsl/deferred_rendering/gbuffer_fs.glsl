#version 330 core
#include "../common/lights.glsl"
#include "../common/parallax.glsl"

layout(std140) uniform SceneBuffer
{
    vec3 camera_position;
};

layout(std140) uniform Material
{
	vec4 diffuse_color;
	vec4 specular_color;

	int use_diffuse_texture;
	int use_specular_texture;
	int use_normal_texture;
	int use_displacement_texture;
	int use_opacity_texture;

	float shininess;
} material;

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
layout (location = 1) out vec4 out_specular;
layout (location = 2) out vec3 out_normal;
layout (location = 3) out vec3 out_position;

vec3 fragment_ambient_color;
vec3 fragment_diffuse_color;
vec3 fragment_specular_color;
vec3 fragment_normal;


void main()
{
    vec2 corrected_texture_coord;
    // displacement
    if (material.use_displacement_texture == 1)
    {
        vec3 tangent_view_dir = normalize(tangent_camera_position - tangent_position);
        corrected_texture_coord = getParallaxTextureCoords(displacement_texture, texture_coord, tangent_view_dir);
    }
    else
        corrected_texture_coord = texture_coord;

    // opacity
    if (material.use_opacity_texture == 1)
    {
        float opacity = texture(opacity_texture, corrected_texture_coord).r;
        if (opacity < MIN_ALPHA_DISCARD)
            discard;
    }

    // diffuse
    if (material.use_diffuse_texture == 1)
    	out_albedo = texture2D(diffuse_texture, corrected_texture_coord).rgb;
    else
        out_albedo = material.diffuse_color.rgb;

    // specular
    if (material.use_specular_texture == 1)
    	out_specular.rgb = vec3(texture2D(specular_texture, corrected_texture_coord).r);
    else
        out_specular.rgb = material.specular_color.rgb;
    out_specular.a = 1.f / material.shininess;

    // normal
    if (material.use_normal_texture == 1)
    	out_normal = normalize(tbn * (texture2D(normal_texture, corrected_texture_coord).rgb * 2.f - 1.f));
    else
        out_normal = normal;
    out_position = position;
}
