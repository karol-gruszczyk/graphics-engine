#include "material.hpp"

using engine::Material;
using engine::ShaderProgram;
using engine::Texture;


Material::Material(ShaderProgram* shader)
	: m_shader(shader)
{}

Material::~Material()
{}

void Material::setDiffuse(const glm::vec3& color)
{
	m_diffuse_color = color;
}

void Material::setDiffuse(Texture* texture)
{
	m_diffuse_texture = texture;
}

void Material::bind() const
{
	if (m_diffuse_texture)
	{
		m_shader->setUniformFloat("material.use_diffuse_texture", true);
		m_diffuse_texture->bind();
	}
	else
		m_shader->setUniformFloat("material.use_diffuse_texture", false);
	m_shader->setUniformVector3("material.diffuse_color", m_diffuse_color);
	m_shader->setUniformFloat("material.shininess", m_shininess);
}

void Material::unbind() const
{
	m_shader->setUniformFloat("material.use_diffuse_texture", false);
	if (m_diffuse_texture)
		m_diffuse_texture->unbind();
}

void engine::Material::setShininess(const float& shininess)
{
	m_shininess = shininess;
}
