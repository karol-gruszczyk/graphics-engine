#include "material.hpp"

using engine::Material;
using engine::ShaderProgram;
using engine::Texture;


Material::Material(ShaderProgram* shader)
	: BasicMaterial(shader)
{}

void Material::bind() const
{
	BasicMaterial::bind();
	m_shader->setUniformFloat("material.shininess", m_shininess);
}

void engine::Material::setShininess(const float& shininess)
{
	m_shininess = shininess;
}
