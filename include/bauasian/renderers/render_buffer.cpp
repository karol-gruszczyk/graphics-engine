#include "render_buffer.hpp"


using bauasian::RenderBuffer;

RenderBuffer::RenderBuffer()
{
	glGenRenderbuffers(1, &m_rbo_id);
}

RenderBuffer::~RenderBuffer()
{
	glDeleteRenderbuffers(1, &m_rbo_id);
}

void RenderBuffer::setSize(const glm::uvec2& size)
{
	glNamedRenderbufferStorageEXT(m_rbo_id, GL_DEPTH24_STENCIL8, size.x, size.y);
}

const GLuint& RenderBuffer::getId() const
{
	return m_rbo_id;
}
