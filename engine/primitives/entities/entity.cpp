#include "entity.h"

using engine::Entity;


Entity::Entity()
{}

Entity::~Entity()
{
	if (m_vao_created)
		glDeleteVertexArrays(1, &m_vao_id);
	if (m_vertex_vbo_created)
		glDeleteBuffers(1, &m_vertex_vbo_id);
	if (m_texture_coords_vbo_created)
		glDeleteBuffers(1, &m_texture_coords_vbo_id);
}

void Entity::updateModelMatrix()
{
	for (auto& shader : m_shaders)
		shader->setUniformMatrix4("model_matrix", m_pivot_matrix);
}
