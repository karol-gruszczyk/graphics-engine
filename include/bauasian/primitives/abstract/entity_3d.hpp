#ifndef BAUASIAN_ENTITY_3D
#define BAUASIAN_ENTITY_3D

#include "renderable.hpp"
#include "renderable_stats.hpp"
#include "affine_transformations_3d.hpp"
#include "bauasian/materials/material.hpp"
#include "bauasian/interfaces/name_interface.hpp"


namespace bauasian
{
	class Entity3D;
}

class bauasian::Entity3D : public Renderable, public RenderableStats, public AffineTransformations3D,
                           public NameInterface
{
public:
	Entity3D(const GLenum& elements_mode, const GLsizei& elements_count, const GLenum& elements_type,
	         const unsigned& num_vertices, const unsigned& num_faces);

	void setMaterial(std::shared_ptr<Material> material);
	void setMaterial(Material* material);
	void render() const override;

protected:
	std::shared_ptr<Material> m_material;

};

#endif /* BAUASIAN_ENTITY_3D */
