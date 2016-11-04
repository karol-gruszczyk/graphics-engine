#ifndef BAUASIAN_FRAME_BUFFER_ATTACHMENT_HPP
#define BAUASIAN_FRAME_BUFFER_ATTACHMENT_HPP

#include "bauasian/mixins/size_mixin.hpp"

#include <GL/glew.h>
#include <glm/glm.hpp>


namespace bauasian
{
	class FrameBufferAttachment;
}

class bauasian::FrameBufferAttachment : public SizeMixin<glm::uvec2>
{
public:
	FrameBufferAttachment(const glm::uvec2& size);
	virtual ~FrameBufferAttachment();

	virtual const GLuint& getId() const = 0;

};

#endif /* BAUASIAN_FRAME_BUFFER_ATTACHMENT_HPP */
