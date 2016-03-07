#include "renderer_2d.h"
#include <glm/gtc/matrix_transform.hpp>

using engine::Renderer2D;


Renderer2D::Renderer2D()
	: Renderer()
{}

Renderer2D::Renderer2D(unsigned context_width, unsigned context_height)
{
	init(context_width, context_height);
}

void Renderer2D::setProjectionMatrix()
{
	m_projection_matrix = glm::ortho(0.f, (float)m_context_width, (float)m_context_height, 0.f);
	m_shader_program->setUniformMatrix4("projection_matrix", m_projection_matrix);
	m_shader_program->setUniformMatrix4("model_matrix", glm::mat4());
}

void Renderer2D::loadDefaultShader()
{
	auto path = Config::getShaderPath();
	m_vertex_shader = std::make_unique<VertexShader>(path / "simple_vs.glsl");
	m_fragment_shader = std::make_unique<FragmentShader>(path / "simple_fs.glsl");
	m_shader_program = std::make_unique<ShaderProgram>();
	m_shader_program->init({ m_vertex_shader.get(), m_fragment_shader.get() });
}

void Renderer2D::setContextWidth(unsigned context_width, unsigned context_height)
{
	Renderer::setContextWidth(context_width, context_height);
	setProjectionMatrix();
}
