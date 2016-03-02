#include "entity.h"

namespace engine
{
	Entity::Entity()
	{
	}

	Entity::~Entity()
	{
		glDeleteBuffers(1, &m_vao);
	}

	void Entity::bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vao);
	}

	void Entity::unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}
