#include "basic_material.hpp"


using engine::BasicMaterial;
using engine::ShaderProgram;


ShaderProgram* BasicMaterial::s_shader;

BasicMaterial::BasicMaterial()
		: m_shader(s_shader)
{}

BasicMaterial::BasicMaterial(const glm::vec3& diffuse_color)
		: BasicMaterial()
{
	m_diffuse_color = diffuse_color;
}

BasicMaterial::BasicMaterial(engine::Texture* diffuse_texture)
		: BasicMaterial()
{
	m_diffuse_texture = diffuse_texture;
}

BasicMaterial::BasicMaterial(ShaderProgram* shader)
		: m_shader(shader)
{}

void BasicMaterial::setName(const std::string& name)
{
	m_name = name;
}

const std::string& BasicMaterial::getName()
{
	return m_name;
}

void BasicMaterial::setDiffuse(const glm::vec3& color)
{
	m_diffuse_color = color;
}

void BasicMaterial::setDiffuse(Texture* texture)
{
	m_diffuse_texture = texture;
}

void BasicMaterial::bind() const
{
	if (m_diffuse_texture)
	{
		m_shader->setUniformBool("material.use_diffuse_texture", true);
		m_diffuse_texture->bind(0);
		m_shader->setUniformInt("material.diffuse_texture", 0);
	}
	else
	{
		m_shader->setUniformBool("material.use_diffuse_texture", false);
		m_shader->setUniformVector3("material.diffuse_color", m_diffuse_color);
	}
}

void BasicMaterial::unbind() const
{
	m_shader->setUniformFloat("material.use_diffuse_texture", false);
	if (m_diffuse_texture)
		m_diffuse_texture->unbind();
}

void BasicMaterial::setDefaultShader(ShaderProgram* shader)
{
	s_shader = shader;
}
