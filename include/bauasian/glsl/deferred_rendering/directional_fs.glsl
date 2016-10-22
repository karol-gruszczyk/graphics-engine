#version 330 core

uniform sampler2D albedo_buffer;
uniform sampler2D specular_buffer;
uniform sampler2D normal_buffer;
uniform sampler2D position_buffer;

in vec2 texture_coord;

out vec3 out_color;


void main()
{
    vec3 diffuse = texture(albedo_buffer, texture_coord).rgb;
    vec4 specular = texture(specular_buffer, texture_coord);
    vec3 normal = texture(normal_buffer, texture_coord).rgb;
    vec3 position = texture(position_buffer, texture_coord).rgb;
    out_color = position;
}
