#include "bloom.hpp"


using bauasian::Bloom;

Bloom::Bloom(const glm::uvec2& size)
{
	m_intensity_texture = std::make_shared<Texture>(GL_RGB16F, GL_RGB, size);
	m_frame_buffer = new FrameBuffer(std::initializer_list<std::shared_ptr<FrameBufferAttachment>>
			{ m_intensity_texture },
			std::make_shared<RenderBuffer>(), size);
	const auto vs = std::make_unique<Shader>("post_processing/basic_vs.glsl", Shader::VERTEX_SHADER);
	const auto fs = std::make_unique<Shader>("post_processing/bloom_fs.glsl", Shader::FRAGMENT_SHADER);
	m_shader = new ShaderProgram({ vs.get(), fs.get() });
}

Bloom::~Bloom()
{
	delete m_frame_buffer;
	delete m_shader;
}
