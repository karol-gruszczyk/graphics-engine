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

	Entity2D(GLenum elements_mode, GLsizei elements_count, GLenum elements_type);

	virtual void setMaterial(const BasicMaterial* material)
	{ m_material = material; }
	virtual void render() const override;

protected:
	const BasicMaterial* m_material = nullptr;

};

#endif /* BAUASIAN_ENTITY_2D_HPP */
