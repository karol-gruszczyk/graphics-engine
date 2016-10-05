#include "entity.hpp"


using bauasian::Entity;


Entity::Entity()
{
	glGenVertexArrays(1, &m_vao_id);
}

Entity::~Entity()
{
	glDeleteVertexArrays(1, &m_vao_id);

	if (m_vbos.size())
		glDeleteBuffers((GLsizei) m_vbos.size(), &m_vbos[0]);
}

void Entity::render() const
{
	glBindVertexArray(m_vao_id);
	glDrawElements(m_draw_mode, m_indices_size, m_elements_type, nullptr);
	glBindVertexArray(0);
}

const glm::mat4& Entity::getModelMatrix() const
{
	return m_model_matrix;
}

const unsigned& Entity::getNumVertices() const
{
	return m_num_vertices;
}

const unsigned& Entity::getNumFaces() const
{
	return m_num_faces;
}

void Entity::setupRendering(GLenum draw_mode, GLuint indices_size, GLenum elements_type)
{
	m_draw_mode = draw_mode;
	m_indices_size = indices_size;
	m_elements_type = elements_type;
}

void Entity::createBufferObject(GLenum target, GLsizeiptr data_length, const void* data, GLenum usage)
{
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(target, vbo);
	glBufferData(target, data_length, data, usage);
	m_vbos.push_back(vbo);
}
