#include "entity_2d.hpp"

#include <glm/gtc/matrix_transform.hpp>


using bauasian::Texture;
using bauasian::Entity2D;


Entity2D::Entity2D(const GLenum& elements_mode, const GLsizei& elements_count, const GLenum& elements_type)
		: IndexedDrawable(elements_mode, elements_count, elements_type)
{}

void Entity2D::setMaterial(bauasian::BasicMaterial* material)
{
	m_material = material;
}

void Entity2D::render() const
{
	if (m_material)
	{
		m_material->bind();
		IndexedDrawable::render();
	}
	else
		IndexedDrawable::render();
}
