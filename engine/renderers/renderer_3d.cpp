#include "renderer_3d.h"
#include <glm/gtc/matrix_transform.hpp>

using engine::Renderer3D;


Renderer3D::Renderer3D()
	: Renderer()
{}

engine::Renderer3D::Renderer3D(unsigned context_width, unsigned context_height)
{
	init(context_width, context_height);
}

void engine::Renderer3D::setContextWidth(unsigned context_width, unsigned context_height)
{
	Renderer::setContextWidth(context_width, context_height);
	updateProjectionMatrix();
}

void engine::Renderer3D::setFieldOfView(GLfloat fov)
{
	m_field_of_view = fov;
	updateProjectionMatrix();
}

GLfloat engine::Renderer3D::getFieldOfView()
{
	return m_field_of_view;
}

void engine::Renderer3D::updateProjectionMatrix()
{
	m_projection_matrix = glm::perspective(m_field_of_view, (GLfloat)m_context_width / m_context_height, 0.1f, 1000.f);
	m_shader_program->setUniformMatrix4("projection_matrix", m_projection_matrix);
	m_shader_program->setUniformMatrix4("view_matrix", glm::mat4());
	m_shader_program->setUniformMatrix4("model_matrix", glm::mat4());
}

void engine::Renderer3D::loadDefaultShader()
{
	auto path = Config::getInstance().getShaderPath();
	m_vertex_shader = std::make_unique<VertexShader>(path / "3d/phong_vs.glsl");
	m_fragment_shader = std::make_unique<FragmentShader>(path / "3d/phong_fs.glsl");
	m_shader_program = std::make_unique<ShaderProgram>();
	m_shader_program->init({ m_vertex_shader.get(), m_fragment_shader.get() });
}
