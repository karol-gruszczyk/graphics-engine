#include "sky_box.hpp"

#include <glm/gtc/matrix_transform.hpp>


using bauasian::SkyBox;

SkyBox::SkyBox(bauasian::CubeTexture* texture)
		: m_texture(texture)
{
	Shader* vertex_shader = new Shader("sky/basic_vs.glsl", Shader::VERTEX_SHADER);
	Shader* fragment_shader = new Shader("sky/basic_fs.glsl", Shader::FRAGMENT_SHADER);
	m_shader_program = new ShaderProgram({ vertex_shader, fragment_shader });
	delete vertex_shader;
	delete fragment_shader;
	m_box = new ScreenCube();

	m_location_projection_view_matrix = m_shader_program->getUniformLocation("projection_view_matrix");
	const auto location_cube_texture = m_shader_program->getUniformLocation("cube_texture");
	m_shader_program->setUniform(location_cube_texture, 0);
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
	m_texture->bind(0);
	m_shader_program->setUniform(m_location_projection_view_matrix, projection_view_matrix);
	m_box->render();
}
