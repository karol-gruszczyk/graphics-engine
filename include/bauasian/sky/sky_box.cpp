#include "sky_box.hpp"


using bauasian::SkyBox;

SkyBox::SkyBox(const boost::filesystem::path& fragment_shader_path)
		: m_box(std::make_unique<ScreenCube>())
{
	const auto vertex_shader = std::make_unique<Shader>("skybox/basic_vs.glsl", Shader::VERTEX_SHADER);
	const auto fragment_shader = std::make_unique<Shader>(fragment_shader_path, Shader::FRAGMENT_SHADER);
	m_shader_program = std::make_unique<ShaderProgram>(
			std::initializer_list<Shader*>{ vertex_shader.get(), fragment_shader.get() });
	m_location_projection_view_matrix = m_shader_program->getUniformLocation("projection_view_matrix");
}

void SkyBox::render(const glm::mat4& projection_view_matrix) const
{
	m_shader_program->use();
	m_shader_program->setUniform(m_location_projection_view_matrix, projection_view_matrix);
	m_box->render();
}
