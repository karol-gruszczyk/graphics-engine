#ifndef BAUASIAN_RENDER_BUFFER_HPP
#define BAUASIAN_RENDER_BUFFER_HPP

#include "frame_buffer_attachment.hpp"


namespace bauasian
{
	class RenderBuffer;
}

class bauasian::RenderBuffer : public FrameBufferAttachment
{
public:
	RenderBuffer(const glm::uvec2& size);
	~RenderBuffer();

	virtual void setSize(const glm::uvec2& size) override;
	virtual GLuint getId() const override
	{ return m_rbo_id; }

private:
	GLuint m_rbo_id;

};

#endif /* BAUASIAN_RENDER_BUFFER_HPP */
