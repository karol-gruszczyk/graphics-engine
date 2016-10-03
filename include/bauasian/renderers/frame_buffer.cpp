#include "frame_buffer.hpp"


using bauasian::FrameBuffer;

FrameBuffer::FrameBuffer(const unsigned& width, const unsigned& height)
{
	glGenFramebuffers(1, &m_fbo_id);

	m_color_texture = new Texture(width, height, GL_RGB, GL_RGB);

	glGenRenderbuffers(1, &m_rbo_id);
	glBindRenderbuffer(GL_RENDERBUFFER, m_rbo_id);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	bind();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_color_texture->getTextureId(), 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo_id);
	assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
	unbind();
}

FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &m_fbo_id);
	glDeleteRenderbuffers(1, &m_rbo_id);
	if (m_color_texture)
		delete m_color_texture;
}

void FrameBuffer::updateSize(const unsigned& width, const unsigned& height) const
{
	m_color_texture->update(width, height, GL_RGB, GL_RGB);

	glBindRenderbuffer(GL_RENDERBUFFER, m_rbo_id);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void FrameBuffer::bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo_id);
}

void FrameBuffer::unbind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
