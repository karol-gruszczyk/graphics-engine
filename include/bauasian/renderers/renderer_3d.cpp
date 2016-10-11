#include "renderer_3d.hpp"
#include "bauasian/shaders/buffers/material_buffer.hpp"
#include "bauasian/shaders/buffers/model_matrices_buffer.hpp"
#include "bauasian/shaders/buffers/scene_buffer.hpp"

#include <glm/gtc/matrix_transform.hpp>


using bauasian::Renderer3D;
using bauasian::Scene3D;

Renderer3D::Renderer3D()
{
	loadShader();
	updateContextSize();
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
	updateProjectionMatrix();
}

void bauasian::Renderer3D::loadShader()
{
	Shader* vertex_shader = new Shader("3d/phong_vs.glsl", Shader::VERTEX_SHADER);
	Shader* fragment_shader = new Shader("3d/phong_fs.glsl", Shader::FRAGMENT_SHADER);
	m_shader_program = new ShaderProgram({ vertex_shader, fragment_shader });
	delete vertex_shader;
	delete fragment_shader;

	const auto& ambient_texture = m_shader_program->getUniformLocation("ambient_texture");
	const auto& diffuse_texture = m_shader_program->getUniformLocation("diffuse_texture");
	const auto& specular_texture = m_shader_program->getUniformLocation("specular_texture");
	const auto& normal_texture = m_shader_program->getUniformLocation("normal_texture");
	m_shader_program->setUniform(ambient_texture, AMBIENT_TEXTURE);
	m_shader_program->setUniform(diffuse_texture, DIFFUSE_TEXTURE);
	m_shader_program->setUniform(specular_texture, SPECULAR_TEXTURE);
	m_shader_program->setUniform(normal_texture, NORMAL_TEXTURE);

	ModelMatricesBuffer::getInstance().attachUniformBlock(m_shader_program, "ModelMatrices");
	MaterialBuffer::getInstance().attachUniformBlock(m_shader_program, "Material");
	SceneBuffer::getInstance().attachUniformBlock(m_shader_program, "SceneBuffer");
}

void Renderer3D::updateContextSize()
{
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
		m_shader_program->use();
		scene->render(m_projection_matrix);

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
	else
	{
		m_shader_program->use();
		scene->render(m_projection_matrix);
	}
}

void Renderer3D::addFilter(Filter* filter)
{
	const auto& size = getContextSize();
	filter->setContextSize(size.x, size.y);
	m_filters.push_back(filter);
}
