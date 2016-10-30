#include "ssao.hpp"


using bauasian::SSAO;
using bauasian::Texture;

SSAO::SSAO(const glm::uvec2& size)
		: ShaderMixin("post_processing/basic_vs.glsl", "post_processing/ssao_fs.glsl")
{
	m_ssao_texture = std::make_shared<Texture>(GL_RED, GL_RED, size);
	m_frame_buffer = std::make_unique<FrameBuffer>(std::initializer_list<std::shared_ptr<FrameBufferAttachment>>
														   { m_ssao_texture },
												   std::make_shared<RenderBuffer>(size), size);

	unsigned kernel_size = 64;
	std::vector<glm::vec3> kernel(kernel_size);

	std::uniform_real_distribution<GLfloat> random_floats(-1.f, 1.f);
	std::default_random_engine generator;
	auto lerp = [](GLfloat a, GLfloat b, GLfloat f) -> GLfloat { return a + f * (b - a); };
	for (auto i = 0u; i < kernel.size(); ++i)
	{
		GLfloat scale = GLfloat(i) / 64;  // accelerating interpolation
		scale = lerp(0.1f, 1.f, scale * scale);
		auto sample = glm::normalize(glm::vec3(
				random_floats(generator),
				random_floats(generator),
				random_floats(generator) / 2.f + 0.5f
		)) * random_floats(generator) / 2.f + 0.5f;
		kernel[i] = sample * scale;
	}

	std::vector<glm::vec3> noise(16);
	for (auto i = 0u; i < noise.size(); ++i)
	{
		noise[i] = glm::vec3(
				random_floats(generator),
				random_floats(generator),
				0.f
		);
	}
	m_noise_texture = std::make_unique<Texture>(glm::uvec2(4, 4), reinterpret_cast<GLubyte*>(noise.data()),
												GL_RGB16F, GL_RGB, false);

}

void SSAO::setSize(const glm::uvec2& size)
{
	m_frame_buffer->setSize(size);
}

void SSAO::process(const FrameBuffer* const frame_buffer) const
{
	frame_buffer->bind();
	glClear(GL_COLOR_BUFFER_BIT);
}
