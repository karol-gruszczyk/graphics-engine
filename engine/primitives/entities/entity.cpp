#include "entity.hpp"

using engine::Entity;


Entity::Entity()
{
	glGenVertexArrays(1, &m_vao_id);
}

Entity::~Entity()
{
	glDeleteVertexArrays(1, &m_vao_id);

	for (auto vbo : m_vbos)
		glDeleteBuffers(1, &vbo);
}

void Entity::render() const
{
	glBindVertexArray(m_vao_id);
	glDrawElements(m_draw_mode, m_elements_size, m_elements_type, nullptr);
	glBindVertexArray(NULL);
}

const glm::mat4& Entity::getModelMatrix() const
{
	return m_model_matrix;
}

void Entity::setupRendering(GLenum draw_mode, GLuint elements_size, GLenum elements_type)
{
	m_draw_mode = draw_mode;
	m_elements_size = elements_size;
	m_elements_type = elements_type;
}

void Entity::createBufferObject(GLenum target, GLsizeiptr data_length, const void* data, GLenum usage /*= GL_STATIC_DRAW*/)
{
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(target, vbo);
	glBufferData(target, data_length, data, usage);
	m_vbos.push_back(vbo);
}
