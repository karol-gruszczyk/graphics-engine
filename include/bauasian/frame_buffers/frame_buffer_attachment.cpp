#include "frame_buffer_attachment.hpp"


using bauasian::FrameBufferAttachment;

FrameBufferAttachment::FrameBufferAttachment(const glm::uvec2& size)
{
	setSize(size);
}

FrameBufferAttachment::~FrameBufferAttachment()
{}
