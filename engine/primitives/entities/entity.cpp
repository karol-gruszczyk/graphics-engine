#include "entity.h"

using engine::Entity;


Entity::Entity()
{}

Entity::~Entity()
{
	if (m_vao_created)
		glDeleteVertexArrays(1, &m_vao_id);

	for (auto vbo : m_vbos)
		glDeleteBuffers(1, &vbo);
}

glm::mat4& Entity::getModelMatrix()
{
	return m_pivot_matrix;
}

void Entity::createBufferObject(GLenum target, GLsizeiptr data_length, const void* data, GLenum usage /*= GL_STATIC_DRAW*/)
{
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(target, vbo);
	glBufferData(target, data_length, data, usage);
	m_vbos.push_back(vbo);
}

void Entity::initBuffers()
{
	glGenVertexArrays(1, &m_vao_id);
	m_vao_created = true;
}
