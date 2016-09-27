#include "material.hpp"


using engine::Material;
using engine::ShaderProgram;
using engine::Texture;


Material::Material()
		: BasicMaterial()
{}

Material::Material(const glm::vec3 &diffuse_color, float shininess /* = 0 */)
		: BasicMaterial(diffuse_color)
{
	m_shininess = shininess;
}

Material::Material(Texture *diffuse_texture, float shininess /* = 0 */)
		: BasicMaterial(diffuse_texture)
{
	m_shininess = shininess;
}

Material::Material(ShaderProgram *shader)
		: BasicMaterial(shader)
{}

void Material::bind() const
{
	BasicMaterial::bind();
	m_shader->setUniformFloat("material.shininess", m_shininess);
}

void engine::Material::setShininess(const float &shininess)
{
	m_shininess = shininess;
}
