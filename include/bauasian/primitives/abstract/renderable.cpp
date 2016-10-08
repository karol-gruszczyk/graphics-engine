#include <numeric>
#include "renderable.hpp"


using bauasian::Renderable;

Renderable::Renderable(const GLenum& elements_mode, const GLsizei& elements_count, const GLenum& elements_type)
		: m_elements_mode(elements_mode), m_elements_count(elements_count), m_elements_type(elements_type)
{
	glGenVertexArrays(1, &m_vao_id);
	glGenBuffers(2, m_vbo_ids);
}

Renderable::~Renderable()
{
	glDeleteVertexArrays(1, &m_vao_id);
	glDeleteBuffers(2, m_vbo_ids);
}

void Renderable::createVertexBuffer(const GLsizeiptr& size, const void* data,
                                    const std::vector<unsigned>& offsets, const GLenum& draw_type) const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_ids[0]);
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
}

void Renderable::createIndexBuffer(const GLsizeiptr& size, const void* data) const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vbo_ids[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void Renderable::render() const
{
	glBindVertexArray(m_vao_id);
	glDrawElements(m_elements_mode, m_elements_count, m_elements_type, nullptr);
}
