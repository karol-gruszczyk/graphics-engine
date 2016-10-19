#ifndef BAUASIAN_ENTITY_3D
#define BAUASIAN_ENTITY_3D

#include "indexed_drawable.hpp"
#include "drawable_stats.hpp"
#include "affine_transformations_3d.hpp"
#include "bauasian/materials/material.hpp"
#include "bauasian/interfaces/name_interface.hpp"


namespace bauasian
{
	class Entity3D;
}

class bauasian::Entity3D : public IndexedDrawable, public DrawableStats, public AffineTransformations3D,
                           public NameInterface
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

	Entity3D(const GLenum& elements_mode, const GLsizei& elements_count, const GLenum& elements_type,
	         const unsigned& num_vertices, const unsigned& num_faces);

	void setMaterial(std::shared_ptr<Material> material);
	void setMaterial(Material* material);
	void render() const override;

protected:
	std::shared_ptr<Material> m_material;

	static void calculateTangents(Vertex3D* vertices, const unsigned short* indices, const unsigned& num_indices);

};

#endif /* BAUASIAN_ENTITY_3D */
