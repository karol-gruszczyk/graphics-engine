#include "renderer_3d.hpp"
#include "bauasian/materials/material.hpp"

#include <glm/gtc/matrix_transform.hpp>


using bauasian::Renderer3D;
using bauasian::Scene3D;

Renderer3D::Renderer3D()
{
	loadShader();
}

Renderer3D::~Renderer3D()
{
	for (auto& filter : m_filters)
		delete filter;
}

const GLfloat& bauasian::Renderer3D::getFieldOfView() const
{
	return m_field_of_view;
}

void bauasian::Renderer3D::setFieldOfView(GLfloat fov)
{
	m_field_of_view = fov;
	updateProjectionMatrix();
}

const GLfloat& Renderer3D::getZNear() const
{
	return m_z_near;
}

void Renderer3D::setZNear(GLfloat z_near)
{
	m_z_near = z_near;
}

const GLfloat& Renderer3D::getZFar() const
{
	return m_z_far;
}

void Renderer3D::setZFar(GLfloat z_far)
{
	m_z_far = z_far;
}

void bauasian::Renderer3D::loadShader()
{
	Shader* vertex_shader = new Shader("3d/phong_vs.glsl", Shader::VERTEX_SHADER);
	Shader* fragment_shader = new Shader("3d/phong_fs.glsl", Shader::FRAGMENT_SHADER);
	m_shader_program = new ShaderProgram({ vertex_shader, fragment_shader });
	Material::setDefaultShader(m_shader_program);
	delete vertex_shader;
	delete fragment_shader;
}

void Renderer3D::updateContextSize()
{
	Renderer::updateContextSize();
	updateProjectionMatrix();
	const auto& size = getContextSize();
	for (auto& filter : m_filters)
		filter->setContextSize(size.x, size.y);
}

void Renderer3D::updateProjectionMatrix()
{
	const auto& size = getContextSize();
	m_projection_matrix = glm::perspective(m_field_of_view, (GLfloat) size.x / size.y, m_z_near, m_z_far);
}

void Renderer3D::render(const Scene3D* scene) const
{
	if (m_filters.size())
	{
		auto it = m_filters.begin();

		(*it)->bind();
		(*it)->clear();
		scene->render(m_shader_program, m_projection_matrix);

		while (true)
		{
			const auto& next = std::next(it);
			if (next == m_filters.end())
				break;
			(*next)->bind();
			(*next)->clear();
			(*it)->renderToScreen();
			it = next;
		}

		(*it)->unbind();
		(*it)->renderToScreen();
	}
	scene->render(m_shader_program, m_projection_matrix);
}

void Renderer3D::addFilter(Filter* filter)
{
	const auto& size = getContextSize();
	filter->setContextSize(size.x, size.y);
	m_filters.push_back(filter);
}
