#ifndef BAUASIAN_BASIC_MATERIAL_HPP
#define BAUASIAN_BASIC_MATERIAL_HPP

#include "bauasian/textures/texture.hpp"
#include "bauasian/buffers/basic_material_buffer.hpp"

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
	BasicMaterial(Texture* diffuse_texture);

	void setDiffuse(const glm::vec3& color);
	void setDiffuse(Texture* texture);

	virtual void bind() const;

protected:
	BasicMaterialBuffer::GlslBasicMaterial m_material;
	Texture* m_diffuse_texture = nullptr;

};

#endif /* BAUASIAN_BASIC_MATERIAL_HPP */
