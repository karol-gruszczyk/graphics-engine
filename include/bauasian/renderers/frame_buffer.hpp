#ifndef BAUASIAN_FRAME_BUFFER_HPP
#define BAUASIAN_FRAME_BUFFER_HPP


#include "bauasian/materials/texture.hpp"
#include <GL/glew.h>


namespace bauasian
{
	class FrameBuffer;
}

class bauasian::FrameBuffer
{
public:
	FrameBuffer(const unsigned& width, const unsigned& height);
	~FrameBuffer();

	void updateSize(const unsigned& width, const unsigned& height) const;
	void bind() const;
	void unbind() const;

private:
	GLuint m_fbo_id, m_rbo_id;
	Texture* m_color_texture = nullptr;
};

#endif /* BAUASIAN_FRAME_BUFFER_HPP */
