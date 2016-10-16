#ifndef BAUASIAN_FRAME_BUFFER_HPP
#define BAUASIAN_FRAME_BUFFER_HPP

#include "render_buffer.hpp"

#include <list>

#include <GL/glew.h>


namespace bauasian
{
	class FrameBuffer;
}

class bauasian::FrameBuffer : public SizeInterface
{
public:
	FrameBuffer(const glm::uvec2& size, const std::initializer_list<FrameBufferAttachment*>& attachments);
	virtual ~FrameBuffer();

	void addAttachment(FrameBufferAttachment* attachment);
	void setSize(const glm::uvec2& size) override;
	void bind() const;
	void unbind() const;
	void clear() const;

protected:
	GLuint m_fbo_id;
	glm::uvec2 m_size;
	std::list<FrameBufferAttachment*> m_attachments;

};

#endif /* BAUASIAN_FRAME_BUFFER_HPP */
