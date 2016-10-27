#include "renderer_2d.hpp"

#include <glm/gtc/matrix_transform.hpp>


using bauasian::Renderer2D;


Renderer2D::Renderer2D()
		: ShaderMixin("2d/basic_vs.glsl", "2d/basic_fs.glsl")
{
	m_location_projection_matrix = m_shader->getUniformLocation("projection_matrix");
	m_location_model_matrix = m_shader->getUniformLocation("model_matrix");
	BasicMaterialBuffer::getInstance().attachUniformBlock(m_shader.get(), "BasicMaterial");

	updateContextSize();
}

void Renderer2D::updateContextSize()
{
	const auto& size = getContextSize();
	m_projection_matrix = glm::ortho(0.f, (float) size.x, (float) size.y, 0.f);
	m_shader->setUniform(m_location_projection_matrix, m_projection_matrix);
}

void Renderer2D::render(const Scene2D* scene) const
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	m_shader->use();
	scene->render(m_shader.get(), m_location_model_matrix);
	glDisable(GL_BLEND);
}

void Renderer2D::clearScreen() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}
