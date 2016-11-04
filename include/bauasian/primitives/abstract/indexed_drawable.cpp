#include "indexed_drawable.hpp"


using bauasian::IndexedDrawable;

IndexedDrawable::IndexedDrawable(GLenum elements_mode, GLsizei elements_count, GLenum elements_type)
		: Drawable(elements_mode, elements_count), m_elements_type(elements_type)
{
	glGenBuffers(1, &m_index_vbo_id);
}

IndexedDrawable::~IndexedDrawable()
{
	glDeleteBuffers(1, &m_index_vbo_id);
}

void IndexedDrawable::render() const
{
	glBindVertexArray(m_vao_id);
	glDrawElements(m_elements_mode, m_elements_count, m_elements_type, nullptr);
}

void IndexedDrawable::updateIndexBuffer(GLsizeiptr size, const void* data, GLenum draw_type) const
{
	glBindVertexArray(m_vao_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_vbo_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, draw_type);
	glBindVertexArray(0);
}
