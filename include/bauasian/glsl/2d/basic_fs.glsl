#version 330

in vec2 texture_coord;

out vec4 out_color;

struct BasicMaterial
{
	vec3 diffuse_color;
	bool use_diffuse_texture;
	sampler2D diffuse_texture;
};

uniform BasicMaterial material;


void main()
{
	out_color = vec4(material.diffuse_color, 1.f);
    if (material.use_diffuse_texture)
    	out_color = texture2D(material.diffuse_texture, texture_coord);
}
