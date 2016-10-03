#include "renderer_2d.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "engine/materials/basic_material.hpp"


using engine::Renderer2D;


Renderer2D::Renderer2D()
{
	loadShader();
}

void Renderer2D::loadShader()
{
	auto path = Engine::getInstance().getShaderPath();
	VertexShader vertex_shader(path / "2d/basic_vs.glsl");
	FragmentShader fragment_shader(path / "2d/basic_fs.glsl");
	m_shader_program = new ShaderProgram({ &vertex_shader, &fragment_shader });
	BasicMaterial::setDefaultShader(m_shader_program);
}

void Renderer2D::updateContextSize()
{
	Renderer::updateContextSize();
	m_projection_matrix = glm::ortho(0.f, (float)s_context_size.x, (float)s_context_size.y, 0.f);
	m_shader_program->setUniformMatrix4("projection_matrix", m_projection_matrix);
}
