#include "renderer_2d.hpp"
#include <glm/gtc/matrix_transform.hpp>

using engine::Renderer2D;


Renderer2D::Renderer2D(const unsigned& context_width, const  unsigned& context_height)
{
	loadShader();
	setContextWidth(context_width, context_height);
}

void Renderer2D::updateProjectionMatrix()
{
	m_projection_matrix = glm::ortho(0.f, (float)m_context_width, (float)m_context_height, 0.f);
	m_shader_program->setUniformMatrix4("projection_matrix", m_projection_matrix);
	m_shader_program->setUniformMatrix4("model_matrix", glm::mat4());
}

void Renderer2D::loadShader()
{
	auto path = Config::getInstance().getShaderPath();
	m_vertex_shader = std::make_unique<VertexShader>(path / "2d/basic_vs.glsl");
	m_fragment_shader = std::make_unique<FragmentShader>(path / "2d/basic_fs.glsl");
	m_shader_program = std::make_unique<ShaderProgram>(std::initializer_list<Shader*>({ m_vertex_shader.get(), m_fragment_shader.get() }));
}

void Renderer2D::setContextWidth(const unsigned& context_width, const unsigned& context_height)
{
	Renderer::setContextWidth(context_width, context_height);
	updateProjectionMatrix();
}
