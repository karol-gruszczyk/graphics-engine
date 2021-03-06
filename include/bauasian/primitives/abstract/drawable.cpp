#include <numeric>
#include "drawable.hpp"


using bauasian::Drawable;

Drawable::Drawable(GLenum elements_mode, GLsizei elements_count)
		: m_elements_mode(elements_mode), m_elements_count(elements_count)
{
	glGenVertexArrays(1, &m_vao_id);
	glGenBuffers(1, &m_vertex_vbo_id);
}

Drawable::~Drawable()
{
	glDeleteVertexArrays(1, &m_vao_id);
	glDeleteBuffers(1, &m_vertex_vbo_id);
}

void Drawable::updateVertexBuffer(GLsizeiptr size, const void* data,
								  const std::vector<unsigned>& offsets, GLenum draw_type) const
{
	glBindVertexArray(m_vao_id);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertex_vbo_id);
	glBufferData(GL_ARRAY_BUFFER, size, data, draw_type);

	unsigned current_offset = 0;
	unsigned floats_per_vertex = std::accumulate(offsets.begin(), offsets.end(), (unsigned)0);
	for (unsigned i = 0; i < offsets.size(); i++)
	{
		glVertexAttribPointer(i, offsets[i], GL_FLOAT, GL_FALSE, floats_per_vertex * sizeof(GLfloat),
		                      reinterpret_cast<void*>(current_offset));
		glEnableVertexAttribArray(i);
		current_offset += offsets[i] * sizeof(GLfloat);
	}

	glBindVertexArray(0);
}

void Drawable::render() const
{
	glBindVertexArray(m_vao_id);
	glDrawArrays(m_elements_mode, 0, m_elements_count);
}
