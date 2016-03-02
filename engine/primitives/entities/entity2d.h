#ifndef ENTITY_2D_H_
#define ENTITY_2D_H_


#include <glm/glm.hpp>
#include "entity.h"

namespace engine
{
	class Entity2D : public engine::Entity
	{
	public:

	protected:
		glm::vec2 m_position;
		GLfloat m_rotation;
	};
}

#endif /* ENTITY_2D_H_ */
