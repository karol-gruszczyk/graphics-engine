#ifndef BAUASIAN_MATERIAL_HPP
#define BAUASIAN_MATERIAL_HPP

#include "bauasian/textures/texture.hpp"
#include "bauasian/shaders/buffers/material_buffer.hpp"
#include "bauasian/mixins/name_mixin.hpp"

#include <memory>


namespace bauasian
{
	class Material;
}

class bauasian::Material : public NameMixin
{
public:
	void setDiffuse(const glm::vec3& color);
	void setDiffuse(Texture* texture);
	void setSpecular(const glm::vec3& color);
	void setSpecular(Texture* texture);
	void setShininess(const float& shininess);
	void setNormalTexture(Texture* texture);
	void setDisplacementTexture(Texture* texture);
	void setOpacityTexture(Texture* texture);

	void bind() const;

protected:
	MaterialBuffer::GlslMaterial m_material;
	Texture* m_diffuse_texture = nullptr;
	Texture* m_specular_texture = nullptr;
	Texture* m_normal_texture = nullptr;
	Texture* m_displacement_texture = nullptr;
	Texture* m_opacity_texture = nullptr;

};

#endif /* BAUASIAN_MATERIAL_HPP */
