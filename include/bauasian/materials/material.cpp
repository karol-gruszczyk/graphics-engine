#include "material.hpp"

#define AMBIENT_TEXTURE 0
#define DIFFUSE_TEXTURE 1
#define SPECULAR_TEXTURE 2
#define NORMAL_TEXTURE 3
#define DISPLACEMENT_TEXTURE 4
#define OPACITY_TEXTURE 5


using bauasian::Material;
using bauasian::ShaderProgram;
using bauasian::Texture;
using bauasian::UniformBuffer;

void Material::setShaderLocations(ShaderProgram* shader)
{
	const auto& ambient_texture = shader->getUniformLocation("ambient_texture");
	const auto& diffuse_texture = shader->getUniformLocation("diffuse_texture");
	const auto& specular_texture = shader->getUniformLocation("specular_texture");
	const auto& normal_texture = shader->getUniformLocation("normal_texture");
	const auto& displacement_texture = shader->getUniformLocation("displacement_texture");
	const auto& opacity_texture = shader->getUniformLocation("opacity_texture");
	shader->setUniform(ambient_texture, AMBIENT_TEXTURE);
	shader->setUniform(diffuse_texture, DIFFUSE_TEXTURE);
	shader->setUniform(specular_texture, SPECULAR_TEXTURE);
	shader->setUniform(normal_texture, NORMAL_TEXTURE);
	shader->setUniform(displacement_texture, DISPLACEMENT_TEXTURE);
	shader->setUniform(opacity_texture, OPACITY_TEXTURE);

	MaterialBuffer::getInstance().attachUniformBlock(shader, "Material");
}

void Material::setAmbient(const glm::vec3& color)
{
	m_material.ambient_color = glm::vec4(color, 1.f);
}

void Material::setAmbient(Texture* texture)
{
	m_ambient_texture = texture;
	m_material.use_ambient_texture = texture != nullptr;
}
void Material::setDiffuse(const glm::vec3& color)
{
	m_material.diffuse_color = glm::vec4(color, 1.f);
}

void Material::setDiffuse(Texture* texture)
{
	m_diffuse_texture = texture;
	m_material.use_diffuse_texture = texture != nullptr;
}

void Material::setSpecular(const glm::vec3& color)
{
	m_material.specular_color = glm::vec4(color, 1.f);
}

void Material::setSpecular(Texture* texture)
{
	m_specular_texture = texture;
	m_material.use_specular_texture = texture != nullptr;
}

void Material::setShininess(const float& shininess)
{
	m_material.shininess = shininess;
}

void Material::setNormalTexture(Texture* texture)
{
	m_normal_texture = texture;
	m_material.use_normal_texture = texture != nullptr;
}

void Material::setDisplacementTexture(Texture* texture)
{
	m_displacement_texture = texture;
	m_material.use_displacement_texture = texture != nullptr;
}

void Material::setOpacityTexture(Texture* texture)
{
	m_opacity_texture = texture;
	m_material.use_opacity_texture = texture != nullptr;
}

void Material::bind() const
{
	if (m_material.use_ambient_texture)
		m_ambient_texture->bind(AMBIENT_TEXTURE);
	if (m_material.use_diffuse_texture)
		m_diffuse_texture->bind(DIFFUSE_TEXTURE);
	if (m_material.use_specular_texture)
		m_specular_texture->bind(SPECULAR_TEXTURE);
	if (m_material.use_normal_texture)
		m_normal_texture->bind(NORMAL_TEXTURE);
	if (m_material.use_displacement_texture)
		m_displacement_texture->bind(DISPLACEMENT_TEXTURE);
	if (m_material.use_opacity_texture)
		m_opacity_texture->bind(OPACITY_TEXTURE);
	MaterialBuffer::getInstance().setData(&m_material);
}
