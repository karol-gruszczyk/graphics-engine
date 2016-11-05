#include "render_buffer.hpp"


using bauasian::RenderBuffer;

RenderBuffer::RenderBuffer(const glm::uvec2& size)
		: FrameBufferAttachment(size)
{
	glGenRenderbuffers(1, &m_rbo_id);
	glNamedRenderbufferStorageEXT(m_rbo_id, GL_DEPTH24_STENCIL8, m_size.x, m_size.y);
}

RenderBuffer::~RenderBuffer()
{
	glDeleteRenderbuffers(1, &m_rbo_id);
}

void RenderBuffer::setSize(const glm::uvec2& size)
{
	FrameBufferAttachment::setSize(size);
	glNamedRenderbufferStorageEXT(m_rbo_id, GL_DEPTH24_STENCIL8, size.x, size.y);
}
