#include "material.hpp"


using bauasian::Material;
using bauasian::ShaderProgram;
using bauasian::Texture;


Material::Material()
		: BasicMaterial()
{}

Material::Material(const glm::vec3& diffuse_color, float shininess /* = 0 */)
		: BasicMaterial(diffuse_color)
{
	m_shininess = shininess;
}

Material::Material(Texture* diffuse_texture, float shininess /* = 0 */)
		: BasicMaterial(diffuse_texture)
{
	m_shininess = shininess;
}

Material::Material(ShaderProgram* shader)
		: BasicMaterial(shader)
{}

void Material::bind() const
{
	BasicMaterial::bind();

	if (m_ambient_texture)
	{
		m_shader->setUniformBool("material.use_ambient_texture", true);
		m_ambient_texture->bind(1);
		m_shader->setUniformInt("material.ambient_texture", 1);
	}
	else
	{
		m_shader->setUniformBool("material.use_ambient_texture", false);
		m_shader->setUniformVector3("material.ambient_color", m_ambient_color);
	}

	if (m_specular_texture)
	{
		m_shader->setUniformBool("material.use_specular_texture", true);
		m_specular_texture->bind(2);
		m_shader->setUniformInt("material.specular_texture", 2);
	}
	else
	{
		m_shader->setUniformBool("material.use_specular_texture", false);
		m_shader->setUniformVector3("material.specular_color", m_specular_color);
	}

	m_shader->setUniformFloat("material.shininess", m_shininess);
}

void Material::setAmbient(const glm::vec3& color)
{
	m_ambient_color = color;
}

void Material::setAmbient(Texture* texture)
{
	m_ambient_texture = texture;
}

void Material::setSpecular(const glm::vec3& color)
{
	m_specular_color = color;
}

void Material::setSpecular(Texture* texture)
{
	m_specular_texture = texture;
}

void bauasian::Material::setShininess(const float& shininess)
{
	m_shininess = shininess;
}
