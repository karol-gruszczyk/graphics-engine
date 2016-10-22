#include "frame_buffer.hpp"
#include "bauasian/materials/texture.hpp"


using bauasian::FrameBuffer;
using bauasian::FrameBufferAttachment;

FrameBuffer::FrameBuffer(const std::initializer_list<FrameBufferAttachment*>& color_attachments,
						 FrameBufferAttachment* depth_attachment, const glm::uvec2& size)
		: SizeInterface(size)
{
	glGenFramebuffers(1, &m_fbo_id);

	if (size.x && size.y)
	{
		for (auto& attachment : color_attachments)
			attachment->setSize(m_size);
		depth_attachment->setSize(m_size);
	}

	GLenum* draw_buffers = new GLenum[color_attachments.size()];
	for (auto& attachment : color_attachments)
	{
		auto i = m_color_attachments.size();
		m_color_attachments.push_back(attachment);
		GLenum color_attachment = GLenum(GL_COLOR_ATTACHMENT0 + i);
		if (auto rbo = dynamic_cast<RenderBuffer*>(attachment))
			glNamedFramebufferRenderbuffer(m_fbo_id, color_attachment, GL_RENDERBUFFER, rbo->getId());
		else if (auto tex = dynamic_cast<Texture*>(attachment))
			glNamedFramebufferTextureEXT(m_fbo_id, color_attachment, tex->getId(), 0);
		draw_buffers[i] = color_attachment;
	}
	glNamedFramebufferDrawBuffers(m_fbo_id, (GLsizei) m_color_attachments.size(), draw_buffers);
	delete[] draw_buffers;

	m_depth_attachment = depth_attachment;
	if (auto rbo = dynamic_cast<RenderBuffer*>(m_depth_attachment))
		glNamedFramebufferRenderbuffer(m_fbo_id, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo->getId());
	else if (auto tex = dynamic_cast<Texture*>(m_depth_attachment))
		glNamedFramebufferTextureEXT(m_fbo_id, GL_DEPTH_STENCIL_ATTACHMENT, tex->getId(), 0);

	assert(glCheckNamedFramebufferStatus(m_fbo_id, GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
}

FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &m_fbo_id);

	for (auto& attachment : m_color_attachments)
		delete attachment;
	delete m_depth_attachment;
}

void FrameBuffer::setSize(const glm::uvec2& size)
{
	SizeInterface::setSize(size);
	for (auto& attachment : m_color_attachments)
		attachment->setSize(size);
	m_depth_attachment->setSize(size);
}

const std::list<FrameBufferAttachment*>& FrameBuffer::getColorAttachments() const
{
	return m_color_attachments;
}

const FrameBufferAttachment* FrameBuffer::getDepthAttachment() const
{
	return m_depth_attachment;
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

void FrameBuffer::copyDepthBuffer(const GLuint& destination_fbo_id) const
{
	glBlitNamedFramebuffer(m_fbo_id, destination_fbo_id, 0, 0, m_size.x, m_size.y, 0, 0, m_size.x, m_size.y, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
}
