#version 330

in vec2 texture_coord;

out vec4 out_color;

layout(std140) uniform BasicMaterial
{
	vec3 diffuse_color;
	int use_diffuse_texture;
};

uniform sampler2D diffuse_texture;


void main()
{
	out_color = vec4(diffuse_color, 1.f);
    if (use_diffuse_texture == 1)
    	out_color = texture2D(diffuse_texture, texture_coord);
}
