#include "entity.h"

using engine::Entity;


Entity::Entity()
{}

Entity::~Entity()
{
	if (m_vao_created)
		glDeleteVertexArrays(1, &m_vao_id);
	if (m_position_vbo_created)
		glDeleteBuffers(1, &m_position_vbo_id);
	if (m_texture_coord_vbo_created)
		glDeleteBuffers(1, &m_texture_coord_vbo_id);
}

glm::mat4& Entity::getModelMatrix()
{
	return m_pivot_matrix;
}
