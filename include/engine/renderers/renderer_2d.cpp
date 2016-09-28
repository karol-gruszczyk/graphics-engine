#include "renderer_2d.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "engine/materials/basic_material.hpp"


using engine::Renderer2D;


Renderer2D::Renderer2D(const unsigned& context_width, const unsigned& context_height)
{
	loadShader();
	setContextWidth(context_width, context_height);
}

void Renderer2D::updateProjectionMatrix()
{
	m_projection_matrix = glm::ortho(0.f, (float) m_context_width, (float) m_context_height, 0.f);
	m_shader_program->setUniformMatrix4("projection_matrix", m_projection_matrix);
	m_shader_program->setUniformMatrix4("model_matrix", glm::mat4());
}

void Renderer2D::loadShader()
{
	auto path = Config::getInstance().getShaderPath();
	VertexShader vertex_shader(path / "2d/basic_vs.glsl");
	FragmentShader fragment_shader(path / "2d/basic_fs.glsl");
	m_shader_program = new ShaderProgram({ &vertex_shader, &fragment_shader });
	BasicMaterial::setDefaultShader(m_shader_program);
}

void Renderer2D::setContextWidth(const unsigned& context_width, const unsigned& context_height)
{
	Renderer::setContextWidth(context_width, context_height);
	updateProjectionMatrix();
}
