#include "bloom.hpp"


using bauasian::Bloom;

Bloom::Bloom(const glm::uvec2& size)
		: ShaderMixin("post_processing/basic_vs.glsl", "post_processing/bloom_fs.glsl")
{
	m_intensity_texture = std::make_shared<Texture>(GL_RGB16F, GL_RGB, size);
	m_frame_buffer = std::make_unique<FrameBuffer>(std::initializer_list<std::shared_ptr<FrameBufferAttachment>>
														   { m_intensity_texture },
												   std::make_shared<RenderBuffer>(size), size);
}
