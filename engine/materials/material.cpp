#include "material.hpp"

using engine::Material;
using engine::ShaderProgram;
using engine::Texture;


Material::Material(ShaderProgram* shader)
	: m_shader(shader)
{}

Material::~Material()
{}

void Material::setAmbient(const glm::vec3& color)
{
	m_ambient_color = color;
}

void Material::setAmbient(Texture* texture)
{
	m_ambient_texture = texture;
}

void Material::setDiffuse(const glm::vec3& color)
{
	m_diffuse_color = color;
}

void Material::setDiffuse(Texture* texture)
{
	m_diffuse_texture = texture;
}

void Material::setSpecular(const glm::vec3& color)
{
	m_specular_color = color;
}

void Material::setSpecular(Texture* texture)
{
	m_specular_texture = texture;
}

void Material::bind() const
{
	m_diffuse_texture->bind();
	m_shader->setUniformFloat("material.shininess", m_shininess);
}

void Material::unbind() const
{

}

void engine::Material::setShininess(const float& shininess)
{
	m_shininess = shininess;
}
