#include "renderer_2d.hpp"
#include "bauasian/shaders/buffers/basic_material_buffer.hpp"

#include <glm/gtc/matrix_transform.hpp>


using bauasian::Renderer2D;


Renderer2D::Renderer2D()
{
	loadShader();
	updateContextSize();
}

void Renderer2D::loadShader()
{
	Shader* vertex_shader = new Shader("2d/basic_vs.glsl", Shader::VERTEX_SHADER);
	Shader* fragment_shader = new Shader("2d/basic_fs.glsl", Shader::FRAGMENT_SHADER);
	m_shader_program = new ShaderProgram({ vertex_shader, fragment_shader });
	delete vertex_shader;
	delete fragment_shader;
	m_location_projection_matrix = m_shader_program->getUniformLocation("projection_matrix");

	BasicMaterialBuffer::getInstance().attachUniformBlock(m_shader_program, "BasicMaterial");
}

void Renderer2D::updateContextSize()
{
	const auto& size = getContextSize();
	m_projection_matrix = glm::ortho(0.f, (float)size.x, (float)size.y, 0.f);
	m_shader_program->setUniform(m_location_projection_matrix, m_projection_matrix);
}

void Renderer2D::render(const Scene2D* scene) const
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	scene->render(m_shader_program, m_projection_matrix);
	glDisable(GL_BLEND);
}
