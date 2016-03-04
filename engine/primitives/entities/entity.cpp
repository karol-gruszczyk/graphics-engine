#include "entity.h"


using engine::Entity;

Entity::Entity()
{
}

Entity::~Entity()
{
	if (m_vao_initialized)
		glDeleteVertexArrays(1, &m_vao_id);
	if (m_vertex_vbo_initialized)
		glDeleteBuffers(1, &m_vertex_vbo_id);
}
