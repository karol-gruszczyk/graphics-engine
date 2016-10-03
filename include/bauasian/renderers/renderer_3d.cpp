#include "renderer_3d.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "bauasian/materials/material.hpp"


using bauasian::Renderer3D;


Renderer3D::Renderer3D()
{
	loadShader();
}

void bauasian::Renderer3D::setFieldOfView(GLfloat fov)
{
	m_field_of_view = fov;
	updateProjectionMatrix();
}

GLfloat bauasian::Renderer3D::getFieldOfView() const
{
	return m_field_of_view;
}

void bauasian::Renderer3D::loadShader()
{
	const auto& path = Engine::getInstance().getShaderPath();
	VertexShader vertex_shader(path / "3d/phong_vs.glsl");
	FragmentShader fragment_shader(path / "3d/phong_fs.glsl");
	m_shader_program = new ShaderProgram({ &vertex_shader, &fragment_shader });
	Material::setDefaultShader(m_shader_program);
}

void Renderer3D::updateContextSize()
{
	Renderer::updateContextSize();
	updateProjectionMatrix();
}

void Renderer3D::updateProjectionMatrix()
{
	m_projection_matrix = glm::perspective(m_field_of_view, (GLfloat) s_context_size.x / s_context_size.y,
	                                       0.1f, 1000.f);
}
