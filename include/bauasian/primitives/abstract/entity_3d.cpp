#include "entity_3d.hpp"


using bauasian::Entity3D;
using bauasian::Material;


Entity3D::Entity3D(const GLenum& elements_mode, const GLsizei& elements_count, const GLenum& elements_type,
                   const unsigned& num_vertices, const unsigned& num_faces)
		: Renderable(elements_mode, elements_count, elements_type), RenderableStats(num_vertices, num_faces)
{}

void Entity3D::setMaterial(std::shared_ptr<Material> material)
{
	m_material = material;
}

void Entity3D::setMaterial(Material* material)
{
	m_material.reset(material);
}

void Entity3D::render() const
{
	if (m_material)
	{
		m_material->bind();
		Renderable::render();
	}
	else
		Renderable::render();
}
