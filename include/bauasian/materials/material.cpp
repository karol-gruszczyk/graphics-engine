#include "material.hpp"


using bauasian::Material;
using bauasian::ShaderProgram;
using bauasian::Texture;
using bauasian::UniformBuffer;


void Material::setName(const std::string& name)
{
	m_name = name;
}

const std::string& Material::getName()
{
	return m_name;
}

void Material::setAmbient(const glm::vec3& color)
{
	m_material.ambient_color = glm::vec4(color, 1.f);
}

void Material::setAmbient(Texture* texture)
{
	m_ambient_texture = texture;
	m_material.use_ambient_texture = 1;
}
void Material::setDiffuse(const glm::vec3& color)
{
	m_material.diffuse_color = glm::vec4(color, 1.f);
}

void Material::setDiffuse(Texture* texture)
{
	m_diffuse_texture = texture;
	m_material.use_diffuse_texture = 1;
}

void Material::setSpecular(const glm::vec3& color)
{
	m_material.specular_color = glm::vec4(color, 1.f);
}

void Material::setSpecular(Texture* texture)
{
	m_specular_texture = texture;
	m_material.use_specular_texture = 1;
}

void Material::setShininess(const float& shininess)
{
	m_material.shininess = shininess;
}

void Material::bind() const
{
	if (m_material.use_ambient_texture)
		m_ambient_texture->bind(AMBIENT_TEXTURE);
	if (m_material.use_diffuse_texture)
		m_diffuse_texture->bind(DIFFUSE_TEXTURE);
	if (m_material.use_specular_texture)
		m_specular_texture->bind(SPECULAR_TEXTURE);
	MaterialBuffer::getInstance().setData(&m_material);
}
