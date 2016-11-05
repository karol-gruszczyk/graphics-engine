#ifndef BAUASIAN_ENTITY_3D
#define BAUASIAN_ENTITY_3D

#include "indexed_drawable.hpp"
#include "drawable_stats.hpp"
#include "affine_transformations_3d.hpp"
#include "bauasian/materials/material.hpp"
#include "bauasian/mixins/name_mixin.hpp"


namespace bauasian
{
	class Entity3D;
}

class bauasian::Entity3D : public IndexedDrawable, public DrawableStats, public AffineTransformations3D,
						   public NameMixin
{
public:
	struct Vertex3D
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 uv;
		glm::vec3 tangent;
		glm::vec3 bi_tangent;

		static const std::vector<unsigned> offsets;
	};

	Entity3D(GLenum elements_mode, GLsizei elements_count, GLenum elements_type, unsigned num_vertices,
			 unsigned num_faces);

	void setMaterial(std::shared_ptr<Material> material)
	{ m_material = material; }
	void render() const override;

protected:
	std::shared_ptr<Material> m_material;

	static void calculateTangents(Vertex3D* vertices, const unsigned* indices, unsigned num_indices);
	static void calculateTangents(Vertex3D* vertices, const unsigned short* indices, unsigned num_indices);

};

#endif /* BAUASIAN_ENTITY_3D */
