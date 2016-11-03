#version 420 core
#include "../locations.glsl"
#include "../bindings.glsl"
#include "../common/lights.glsl"

layout (location = DEFERRED_GBUFFER_POSITION) in vec3 vertex_position;
layout (location = DEFERRED_GBUFFER_NORMAL) in vec3 vertex_normal;
layout (location = DEFERRED_GBUFFER_TEXTURE_COORD) in vec2 vertex_texture_coord;
layout (location = DEFERRED_GBUFFER_TANGENT) in vec3 vertex_tangent;
layout (location = DEFERRED_GBUFFER_BI_TANGENT) in vec3 vertex_bi_tangent;

layout(std140, binding = BUFFER_CAMERA_BINDING) uniform CameraBuffer
{
    mat4 projection_matrix;
    mat4 view_matrix;
    vec3 position;
	float near;
	float far;
} camera;

layout(std140, binding = BUFFER_MATRICES_BINDING) uniform MatricesBuffer
{
    mat4 model_matrix;
    mat4 normal_matrix;
};

out vec3 position;
out vec2 texture_coord;
out vec3 normal;
out mat3 tbn;
out vec3 tangent_position;
out vec3 tangent_camera_position;


void main()
{
    vec4 world_space_position = model_matrix * vec4(vertex_position, 1.f);
	position = vec3(world_space_position);
	texture_coord = vertex_texture_coord;
	normal = normalize(mat3(normal_matrix) * vertex_normal);
	gl_Position = camera.projection_matrix * camera.view_matrix * world_space_position;

    tbn = mat3(normal_matrix) * mat3(vertex_tangent, vertex_bi_tangent, vertex_normal);

    mat3 TBN = transpose(tbn);
    tangent_position = TBN * position;
    tangent_camera_position = TBN * camera.position;
}
