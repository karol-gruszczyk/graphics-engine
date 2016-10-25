#include "sky_box.hpp"


using bauasian::SkyBox;

SkyBox::SkyBox(const boost::filesystem::path& fragment_shader_path)
{
	auto vertex_shader = std::make_unique<Shader>("skybox/basic_vs.glsl", Shader::VERTEX_SHADER);
	auto fragment_shader = std::make_unique<Shader>(fragment_shader_path, Shader::FRAGMENT_SHADER);
	m_shader_program = new ShaderProgram({ vertex_shader.get(), fragment_shader.get() });
	m_box = new ScreenCube();

	m_location_projection_view_matrix = m_shader_program->getUniformLocation("projection_view_matrix");
}

SkyBox::~SkyBox()
{
	delete m_shader_program;
	delete m_box;
}

void SkyBox::render(const glm::mat4& projection_view_matrix) const
{
	m_shader_program->use();
	m_shader_program->setUniform(m_location_projection_view_matrix, projection_view_matrix);
	m_box->render();
}
