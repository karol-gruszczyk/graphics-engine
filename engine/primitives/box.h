#ifndef BOX_H_
#define BOX_H_

#include "entities/entity_3d.h"


namespace engine
{
	class Box;
}

class engine::Box : public Entity3D
{
public:
	Box(glm::vec3 size, glm::vec3 position = { 0.f, 0.f, 0.f }, glm::vec3 rotation = { 0.f, 0.f, 0.f }, glm::vec3 scale = { 1.f, 1.f, 1.f }, 
		glm::vec3 pivot = { 0.f, 0.f, 0.f });
private:
	GLfloat m_width, m_length, m_height;
};

#endif /* BOX_H_ */
