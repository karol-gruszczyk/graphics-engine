#include "entity_2d.hpp"


using bauasian::Texture;
using bauasian::Entity2D;

Entity2D::Entity2D(GLenum elements_mode, GLsizei elements_count, GLenum elements_type)
		: IndexedDrawable(elements_mode, elements_count, elements_type)
{}

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
