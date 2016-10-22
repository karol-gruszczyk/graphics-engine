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
	FrameBuffer(const std::initializer_list<FrameBufferAttachment*>& color_attachments,
	            FrameBufferAttachment* depth_attachment, const glm::uvec2& size = { 0, 0 });
	virtual ~FrameBuffer();

	void setSize(const glm::uvec2& size) override;

	const GLuint& getId() const;
	const std::list<FrameBufferAttachment*>& getColorAttachments() const;
	const FrameBufferAttachment* getDepthAttachment() const;
	void bind() const;
	void unbind() const;
	void clear() const;
	void copyDepthBuffer(const GLuint& destination_fbo_id = 0) const;

protected:
	GLuint m_fbo_id;
	std::list<FrameBufferAttachment*> m_color_attachments;
	FrameBufferAttachment* m_depth_attachment;

};

#endif /* BAUASIAN_FRAME_BUFFER_HPP */
