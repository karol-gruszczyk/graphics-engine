#include "bloom.hpp"


using bauasian::Bloom;

Bloom::Bloom(const glm::uvec2& size)
{
	m_intensity_texture = new Texture(GL_RGB16F, GL_RGB, size);
	m_frame_buffer = new FrameBuffer({ m_intensity_texture }, new RenderBuffer(), size);
	auto vs = std::make_unique<Shader>("post_processing/basic_vs.glsl", Shader::VERTEX_SHADER);
	auto fs = std::make_unique<Shader>("post_processing/bloom_fs.glsl", Shader::FRAGMENT_SHADER);
	m_shader = new ShaderProgram({ vs.get(), fs.get() });
}

Bloom::~Bloom()
{
	delete m_frame_buffer;
	delete m_intensity_texture;
	delete m_shader;
}
