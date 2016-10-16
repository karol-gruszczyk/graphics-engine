#include "frame_buffer.hpp"


using bauasian::FrameBuffer;

FrameBuffer::FrameBuffer(const glm::uvec2& size, const std::initializer_list<FrameBufferAttachment*>& attachments)
		: SizeInterface(size)
{
	glGenFramebuffers(1, &m_fbo_id);

	for (auto& attachment : attachments)
	{
		addAttachment(attachment);
	}
}

FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &m_fbo_id);

	for (auto& attachment : m_attachments)
		delete attachment;
}

void FrameBuffer::addAttachment(bauasian::FrameBufferAttachment* attachment)
{
	m_attachments.push_back(attachment);
	attachment->setSize(m_size);
	if (auto render_buffer = dynamic_cast<RenderBuffer*>(attachment))
		glNamedFramebufferRenderbuffer(m_fbo_id, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, render_buffer->getId());
}

void FrameBuffer::setSize(const glm::uvec2& size)
{
	SizeInterface::setSize(size);
	for (auto& attachment : m_attachments)
		attachment->setSize(size);
}

void FrameBuffer::bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo_id);
}

void FrameBuffer::unbind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::clear() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
