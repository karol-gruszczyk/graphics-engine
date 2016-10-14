#include "sky_box.hpp"


using bauasian::SkyBox;

SkyBox::SkyBox(const boost::filesystem::path& fragment_shader_path)
{
	Shader* vertex_shader = new Shader("sky/basic_vs.glsl", Shader::VERTEX_SHADER);
	Shader* fragment_shader = new Shader(fragment_shader_path, Shader::FRAGMENT_SHADER);
	m_shader_program = new ShaderProgram({ vertex_shader, fragment_shader });
	delete vertex_shader;
	delete fragment_shader;
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
	glDepthFunc(GL_LEQUAL);
	m_shader_program->use();
	m_shader_program->setUniform(m_location_projection_view_matrix, projection_view_matrix);
	m_box->render();
}
