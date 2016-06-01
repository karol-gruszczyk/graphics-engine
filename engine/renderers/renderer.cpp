#include "renderer.h"

using engine::Renderer;


Renderer::Renderer()
{}

void Renderer::setContextWidth(unsigned context_width, unsigned context_height)
{
	glViewport(0, 0, context_width, context_height);
	m_context_width = context_width;
	m_context_height = context_height;
}

void Renderer::clearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

glm::mat4& Renderer::getProjectionMatrix()
{
	return m_projection_matrix;
}
