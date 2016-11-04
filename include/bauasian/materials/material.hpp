#ifndef BAUASIAN_MATERIAL_HPP
#define BAUASIAN_MATERIAL_HPP

#include "bauasian/textures/texture.hpp"
#include "bauasian/uniform_buffers/material_buffer.hpp"
#include "bauasian/mixins/name_mixin.hpp"

#include <memory>


namespace bauasian
{
	class Material;
}

class bauasian::Material final : public NameMixin
{
public:
	void setDiffuse(const glm::vec3& color);
	void setDiffuse(const Texture* texture);
	void setSpecular(const glm::vec3& color);
	void setSpecular(const Texture* texture);
	void setShininess(float shininess);
	void setNormalTexture(const Texture* texture);
	void setDisplacementTexture(const Texture* texture);
	void setOpacityTexture(const Texture* texture);

	void bind() const;

private:
	MaterialBuffer m_buffer;
	const Texture* m_diffuse_texture = nullptr;
	const Texture* m_specular_texture = nullptr;
	const Texture* m_normal_texture = nullptr;
	const Texture* m_displacement_texture = nullptr;
	const Texture* m_opacity_texture = nullptr;

};

#endif /* BAUASIAN_MATERIAL_HPP */
