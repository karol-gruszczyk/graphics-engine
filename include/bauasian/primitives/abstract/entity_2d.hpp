#ifndef BAUASIAN_ENTITY_2D_HPP
#define BAUASIAN_ENTITY_2D_HPP

#include "indexed_drawable.hpp"
#include "affine_transformations_2d.hpp"
#include "bauasian/materials/basic_material.hpp"


namespace bauasian
{
	class Entity2D;
}

class bauasian::Entity2D : public IndexedDrawable, public AffineTransformations2D
{
public:
	struct Vertex2D
	{
		glm::vec2 position;
		glm::vec2 uv;
	};

	Entity2D(const GLenum& elements_mode, const GLsizei& elements_count, const GLenum& elements_type);

	virtual void setMaterial(BasicMaterial* material);
	virtual void render() const override;

protected:
	BasicMaterial* m_material = nullptr;

};

#endif /* BAUASIAN_ENTITY_2D_HPP */
