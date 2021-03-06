#version 420 core
#include "../globals.glsl"
#include "../uniform_buffers/camera_buffer.glsl"
#include "../uniform_buffers/material_buffer.glsl"
#include "../common/parallax.glsl"
#include "../utils/linearize_depth.glsl"


layout (binding = MATERIAL_DIFFUSE_BINDING) uniform sampler2D diffuse_texture;
layout (binding = MATERIAL_SPECULAR_BINDING) uniform sampler2D specular_texture;
layout (binding = MATERIAL_NORMAL_BINDING) uniform sampler2D normal_texture;
layout (binding = MATERIAL_DISPLACEMENT_BINDING) uniform sampler2D displacement_texture;
layout (binding = MATERIAL_OPACITY_BINDING) uniform sampler2D opacity_texture;

in vec3 position;
in vec2 texture_coord;
in vec3 normal;
in mat3 tbn;
in vec3 tangent_position;
in vec3 tangent_camera_position;

layout (location = DEFERRED_ALBEDO_BINDING) out vec3 out_albedo;
layout (location = DEFERRED_SPECULAR_BINDING) out vec4 out_specular;
layout (location = DEFERRED_NORMAL_BINDING) out vec3 out_normal;
layout (location = DEFERRED_POSITION_BINDING) out vec4 out_position;


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
    out_position = vec4(position, linearizeDepth(gl_FragCoord.z, camera.near, camera.far));
}
