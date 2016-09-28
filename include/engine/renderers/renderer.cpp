#include "renderer.hpp"


using engine::Renderer;
using engine::ShaderProgram;


Renderer::Renderer()
{}

Renderer::~Renderer()
{
	if (m_shader_program)
		delete m_shader_program;
}

void Renderer::setContextWidth(const unsigned& context_width, const unsigned& context_height)
{
	glViewport(0, 0, context_width, context_height);
	m_context_width = context_width;
	m_context_height = context_height;
}

void Renderer::clearScreen() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

ShaderProgram* Renderer::getShaderProgram() const
{
	return m_shader_program;
}

const glm::mat4& Renderer::getProjectionMatrix() const
{
	return m_projection_matrix;
}
