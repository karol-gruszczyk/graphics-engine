#include "renderer_3d.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "engine/materials/material.hpp"


using engine::Renderer3D;


Renderer3D::Renderer3D(const unsigned& context_width, const unsigned& context_height)
{
	loadShader();
	setContextWidth(context_width, context_height);
}

void engine::Renderer3D::setContextWidth(const unsigned& context_width, const unsigned& context_height)
{
	Renderer::setContextWidth(context_width, context_height);
	updateProjectionMatrix();
}

void engine::Renderer3D::setFieldOfView(GLfloat fov)
{
	m_field_of_view = fov;
	updateProjectionMatrix();
}

GLfloat engine::Renderer3D::getFieldOfView() const
{
	return m_field_of_view;
}

void engine::Renderer3D::updateProjectionMatrix()
{
	m_projection_matrix = glm::perspective(m_field_of_view, (GLfloat) m_context_width / m_context_height, 0.1f, 1000.f);
}

void engine::Renderer3D::loadShader()
{
	const auto& path = Config::getInstance().getShaderPath();
	VertexShader vertex_shader(path / "3d/phong_vs.glsl");
	FragmentShader fragment_shader(path / "3d/phong_fs.glsl");
	m_shader_program = new ShaderProgram({ &vertex_shader, &fragment_shader });
	Material::setDefaultShader(m_shader_program);
}
