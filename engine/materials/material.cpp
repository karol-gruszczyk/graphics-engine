#include "material.h"

using engine::Material;
using engine::ShaderProgram;
using engine::Texture;


Material::Material(ShaderProgram* shader)
	: m_shader(shader)
{}

Material::~Material()
{}

void Material::setAmbient(glm::vec3 color)
{
	m_ambient_color = color;
}

void Material::setAmbient(Texture* texture)
{
	m_ambient_texture = texture;
}

void Material::setDiffuse(glm::vec3 color)
{
	m_diffuse_color = color;
}

void Material::setDiffuse(Texture* texture)
{
	m_diffuse_texture = texture;
}

void Material::setSpecular(glm::vec3 color)
{
	m_specular_color = color;
}

void Material::setSpecular(Texture* texture)
{
	m_specular_texture = texture;
}

void Material::bind()
{
	m_diffuse_texture->bind();
	m_shader->setUniformFloat("material.shininess", m_shininess);
}

void Material::unbind()
{

}

void engine::Material::setShininess(float shininess)
{
	m_shininess = shininess;
}
