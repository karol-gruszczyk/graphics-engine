#include "renderer_2d.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "bauasian/materials/basic_material.hpp"


using bauasian::Renderer2D;


Renderer2D::Renderer2D()
{
	loadShader();
}

void Renderer2D::loadShader()
{
	Shader* vertex_shader = new Shader("2d/basic_vs.glsl", Shader::VERTEX_SHADER);
	Shader* fragment_shader = new Shader("2d/basic_fs.glsl", Shader::FRAGMENT_SHADER);
	m_shader_program = new ShaderProgram({ vertex_shader, fragment_shader });
	BasicMaterial::setDefaultShader(m_shader_program);
	delete vertex_shader;
	delete fragment_shader;
}

void Renderer2D::updateContextSize()
{
	Renderer::updateContextSize();
	const auto& size = getContextSize();
	m_projection_matrix = glm::ortho(0.f, (float)size.x, (float)size.y, 0.f);
	m_shader_program->setUniformMatrix4("projection_matrix", m_projection_matrix);
}

void Renderer2D::render(const bauasian::Scene2D* scene) const
{
	scene->render(m_shader_program, m_projection_matrix);
}
