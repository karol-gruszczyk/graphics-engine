#ifndef BAUASIAN_BASIC_MATERIAL_HPP
#define BAUASIAN_BASIC_MATERIAL_HPP

#include "bauasian/textures/texture.hpp"
#include "bauasian/uniform_buffers/basic_material_buffer.hpp"

#include <glm/glm.hpp>


namespace bauasian
{
	class BasicMaterial;
}

class bauasian::BasicMaterial
{
public:
	BasicMaterial();
	BasicMaterial(const glm::vec3& diffuse_color);
	BasicMaterial(Texture* const diffuse_texture);

	void setDiffuse(const glm::vec3& color);
	void setDiffuse(const Texture* texture);

	virtual void bind() const;

protected:
	BasicMaterialBuffer::GlslBasicMaterial m_material;
	const Texture* m_diffuse_texture = nullptr;

};

#endif /* BAUASIAN_BASIC_MATERIAL_HPP */
