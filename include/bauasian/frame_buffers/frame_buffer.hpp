#ifndef BAUASIAN_FRAME_BUFFER_HPP
#define BAUASIAN_FRAME_BUFFER_HPP

#include "render_buffer.hpp"

#include <list>
#include <memory>

#include <GL/glew.h>


namespace bauasian
{
	class FrameBuffer;
}

class bauasian::FrameBuffer
{
public:
	FrameBuffer(const std::initializer_list<std::shared_ptr<FrameBufferAttachment>>& color_attachments,
				const std::shared_ptr<FrameBufferAttachment>& depth_attachment, const glm::uvec2& size);
	virtual ~FrameBuffer();

	void setSize(const glm::uvec2& size);

	GLuint getId() const
	{ return m_fbo_id; }
	const std::list<std::shared_ptr<FrameBufferAttachment>>& getColorAttachments() const
	{ return m_color_attachments; }
	const std::shared_ptr<FrameBufferAttachment>& getDepthAttachment() const
	{ return m_depth_attachment; }
	void bind() const;
	void unbind() const;
	void copyBuffer(GLbitfield mask, GLuint destination_fbo_id = 0) const;

protected:
	GLuint m_fbo_id;
	glm::uvec2 m_size;
	std::list<std::shared_ptr<FrameBufferAttachment>> m_color_attachments;
	std::shared_ptr<FrameBufferAttachment> m_depth_attachment;

};

#endif /* BAUASIAN_FRAME_BUFFER_HPP */
