#include "fxaa.hpp"


using bauasian::FXAA;
using bauasian::Texture;

FXAA::FXAA(const glm::uvec2& size, Quality quality)
		: m_screen_quad(std::make_unique<ScreenQuad>())
{
	const auto vs = std::make_unique<Shader>("post_processing/basic_vs.glsl", Shader::VERTEX_SHADER);
	const auto fs = std::make_unique<Shader>("post_processing/fxaa_fs.glsl", Shader::FRAGMENT_SHADER,
											 std::map<std::string, std::string>
													 {{ "FXAA_QUALITY__PRESET", std::to_string(quality) }});
	m_shader = std::make_unique<ShaderProgram>(std::initializer_list<const Shader*>{ vs.get(), fs.get() });
	m_location_pixel_size = m_shader->getUniformLocation("pixel_size");
	m_location_subpix = m_shader->getUniformLocation("subpix");
	m_location_edge_threshold = m_shader->getUniformLocation("edge_threshold");
	m_location_edge_threshold_min = m_shader->getUniformLocation("edge_threshold_min");
	m_shader->setUniform(m_location_pixel_size, 1.f / glm::vec2(size));

	m_color_texture = std::make_shared<Texture>(GL_RGB, GL_RGB, size);
	m_frame_buffer = std::make_unique<FrameBuffer>(std::initializer_list<std::shared_ptr<FrameBufferAttachment>>
														   { m_color_texture },
												   std::make_shared<RenderBuffer>(size), size);
}

void FXAA::setSize(const glm::uvec2& size)
{
	m_frame_buffer->setSize(size);
	m_shader->setUniform(m_location_pixel_size, 1.f / glm::vec2(size));
}

void FXAA::process(unsigned short out_binding) const
{
	m_frame_buffer->bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_shader->use();
	m_screen_quad->render();

	m_color_texture->bind(out_binding);
}

void FXAA::processToScreen() const
{
	m_frame_buffer->unbind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_shader->use();
	m_screen_quad->render();
}

void FXAA::process(const Texture* texture) const
{
	texture->bind(POST_PROCESSING_COLOR_TEXTURE);
	m_frame_buffer->unbind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_shader->use();
	m_screen_quad->render();
}

const Texture* FXAA::getTexture() const
{
	return m_color_texture.get();
}

void FXAA::setSubPixelRemoval(float sub_pixel_removal) const
{
	m_shader->setUniform(m_location_subpix, sub_pixel_removal);
}

void FXAA::setEdgeThreshold(float edge_threshold) const
{
	m_shader->setUniform(m_location_edge_threshold, edge_threshold);
}

void FXAA::setEdgeThresholdMin(float edge_threshold_min) const
{
	m_shader->setUniform(m_location_edge_threshold_min, edge_threshold_min);
}
