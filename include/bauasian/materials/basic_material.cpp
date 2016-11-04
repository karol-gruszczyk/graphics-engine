#include "basic_material.hpp"


using bauasian::BasicMaterial;


BasicMaterial::BasicMaterial()
{}

BasicMaterial::BasicMaterial(const glm::vec3& diffuse_color)
		: BasicMaterial()
{
	setDiffuse(diffuse_color);
}

BasicMaterial::BasicMaterial(Texture* const diffuse_texture)
		: BasicMaterial()
{
	setDiffuse(diffuse_texture);
}

void BasicMaterial::setDiffuse(const glm::vec3& color)
{
	m_material.diffuse_color = color;
}

void BasicMaterial::setDiffuse(const Texture* texture)
{
	m_diffuse_texture = texture;
	m_material.use_diffuse_texture = 1;
}

void BasicMaterial::bind() const
{
	if (m_diffuse_texture)
		m_diffuse_texture->bind(0);
	BasicMaterialBuffer::getInstance().setData(&m_material);
}
