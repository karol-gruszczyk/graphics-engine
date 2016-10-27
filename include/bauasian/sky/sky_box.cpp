#include "sky_box.hpp"


using bauasian::SkyBox;

SkyBox::SkyBox(const boost::filesystem::path& fragment_shader_path)
		: ShaderMixin("skybox/basic_vs.glsl", fragment_shader_path), m_box(std::make_unique<ScreenCube>())
{
	m_location_projection_view_matrix = m_shader->getUniformLocation("projection_view_matrix");
}

void SkyBox::render(const glm::mat4& projection_view_matrix) const
{
	m_shader->use();
	m_shader->setUniform(m_location_projection_view_matrix, projection_view_matrix);
	m_box->render();
}
