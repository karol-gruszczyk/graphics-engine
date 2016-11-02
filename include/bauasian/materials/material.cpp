#include "material.hpp"
#include "bauasian/glsl/bindings.glsl"


using bauasian::Material;
using bauasian::ShaderProgram;
using bauasian::Texture;
using bauasian::UniformBuffer;

void Material::setDiffuse(const glm::vec3& color)
{
	m_buffer.setDiffuseColor(color);
}

void Material::setDiffuse(Texture* texture)
{
	m_diffuse_texture = texture;
	m_buffer.setUseDiffuseTexture(texture != nullptr);
}

void Material::setSpecular(const glm::vec3& color)
{
	m_buffer.setSpecularColor(color);
}

void Material::setSpecular(Texture* texture)
{
	m_specular_texture = texture;
	m_buffer.setUseSpecularTexture(texture != nullptr);
}

void Material::setShininess(const float& shininess)
{
	m_buffer.setShininess(shininess);
}

void Material::setNormalTexture(Texture* texture)
{
	m_normal_texture = texture;
	m_buffer.setUseNormalTexture(texture != nullptr);
}

void Material::setDisplacementTexture(Texture* texture)
{
	m_displacement_texture = texture;
	m_buffer.setUseDiffuseTexture(texture != nullptr);
}

void Material::setOpacityTexture(Texture* texture)
{
	m_opacity_texture = texture;
	m_buffer.setUseOpacityTexture(texture != nullptr);
}

void Material::bind() const
{
	if (m_diffuse_texture)
		m_diffuse_texture->bind(MATERIAL_DIFFUSE_BINDING);
	if (m_specular_texture)
		m_specular_texture->bind(MATERIAL_SPECULAR_BINDING);
	if (m_normal_texture)
		m_normal_texture->bind(MATERIAL_NORMAL_BINDING);
	if (m_displacement_texture)
		m_displacement_texture->bind(MATERIAL_DISPLACEMENT_BINDING);
	if (m_opacity_texture)
		m_opacity_texture->bind(MATERIAL_OPACITY_BINDING);
	m_buffer.bind();
}
