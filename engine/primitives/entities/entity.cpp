#include "entity.h"

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

glm::mat4& Entity::getModelMatrix()
{
	return m_model_matrix;
}

void Entity::createBufferObject(GLenum target, GLsizeiptr data_length, const void* data, GLenum usage /*= GL_STATIC_DRAW*/)
{
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(target, vbo);
	glBufferData(target, data_length, data, usage);
	m_vbos.push_back(vbo);
}
