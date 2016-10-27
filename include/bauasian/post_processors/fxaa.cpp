#include "fxaa.hpp"


using bauasian::FXAA;

FXAA::FXAA(const Quality& quality)
		: AreaFilter(*std::make_unique<Shader>("post_processing/fxaa_fs.glsl",
		                                       Shader::FRAGMENT_SHADER,
		                                       std::map<std::string, std::string>(
				                                       {{"FXAA_QUALITY__PRESET", std::to_string(quality)}})))
{
	m_location_subpix = m_shader->getUniformLocation("subpix");
	m_location_edge_threshold = m_shader->getUniformLocation("edge_threshold");
	m_location_edge_threshold_min = m_shader->getUniformLocation("edge_threshold_min");
}

void FXAA::setQuality(const Quality& quality)
{
	const auto vertex_shader = new Shader("post_processing/fxaa_fs.glsl", Shader::FRAGMENT_SHADER,
	                                      {{"FXAA_QUALITY__PRESET", std::to_string(quality)}});
	loadShader(*vertex_shader);
	delete vertex_shader;
}

void FXAA::setSubPixelRemoval(const float& sub_pixel_removal) const
{
	m_shader->setUniform(m_location_subpix, sub_pixel_removal);
}

void FXAA::setEdgeThreshold(const float& edge_threshold) const
{
	m_shader->setUniform(m_location_edge_threshold, edge_threshold);
}

void FXAA::setEdgeThresholdMin(const float& edge_threshold_min) const
{
	m_shader->setUniform(m_location_edge_threshold_min, edge_threshold_min);
}
