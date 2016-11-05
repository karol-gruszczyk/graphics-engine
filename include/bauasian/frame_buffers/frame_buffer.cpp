#include "frame_buffer.hpp"
#include "bauasian/textures/texture.hpp"


using bauasian::FrameBuffer;
using bauasian::FrameBufferAttachment;

FrameBuffer::FrameBuffer(const std::initializer_list<std::shared_ptr<FrameBufferAttachment>>& color_attachments,
						 const std::shared_ptr<FrameBufferAttachment>& depth_attachment, const glm::uvec2& size)
		: m_size(size)
{
	glCreateFramebuffers(1, &m_fbo_id);

	if (color_attachments.size())
	{
		GLenum* draw_buffers = new GLenum[color_attachments.size()];
		for (auto& attachment : color_attachments)
		{
			auto i = m_color_attachments.size();
			m_color_attachments.push_back(attachment);
			GLenum color_attachment = GLenum(GL_COLOR_ATTACHMENT0 + i);
			if (auto rbo = dynamic_cast<RenderBuffer*>(attachment.get()))
				glNamedFramebufferRenderbuffer(m_fbo_id, color_attachment, GL_RENDERBUFFER, rbo->getId());
			else if (auto tex = dynamic_cast<Texture*>(attachment.get()))
				glNamedFramebufferTextureEXT(m_fbo_id, color_attachment, tex->getId(), 0);
			draw_buffers[i] = color_attachment;
		}
		glNamedFramebufferDrawBuffers(m_fbo_id, (GLsizei) m_color_attachments.size(), draw_buffers);
		delete[] draw_buffers;
	}
	else
		glNamedFramebufferDrawBuffer(m_fbo_id, GL_NONE);

	m_depth_attachment = depth_attachment;
	if (auto rbo = dynamic_cast<RenderBuffer*>(m_depth_attachment.get()))
		glNamedFramebufferRenderbuffer(m_fbo_id, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo->getId());
	else if (auto tex = dynamic_cast<Texture*>(m_depth_attachment.get()))
		glNamedFramebufferTexture(m_fbo_id, GL_DEPTH_ATTACHMENT, tex->getId(), 0);

	assert(glCheckNamedFramebufferStatus(m_fbo_id, GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
}

FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &m_fbo_id);
}

void FrameBuffer::setSize(const glm::uvec2& size)
{
	for (auto& attachment : m_color_attachments)
		attachment->setSize(size);
	m_depth_attachment->setSize(size);
}

void FrameBuffer::bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo_id);
}

void FrameBuffer::unbind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::copyBuffer(GLbitfield mask, GLuint destination_fbo_id) const
{
	glBlitNamedFramebuffer(m_fbo_id, destination_fbo_id,
						   0, 0, m_size.x, m_size.y, 0, 0, m_size.x, m_size.y,
						   mask, GL_NEAREST);
}
