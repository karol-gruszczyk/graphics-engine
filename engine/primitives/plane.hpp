#ifndef PLANE_HPP_
#define PLANE_HPP_

#include "entities/entity_3d.hpp"


namespace engine
{
	class Plane;
}

class engine::Plane : public Entity3D
{
public:
	Plane(glm::vec2 size, glm::vec3 position = { 0.f, 0.f, 0.f }, unsigned tile = 1, glm::vec3 rotation = { 0.f, 0.f, 0.f }, 
		glm::vec3 scale = { 1.f, 1.f, 1.f }, glm::vec3 pivot = { 0.f, 0.f, 0.f });
private:
	GLfloat m_width, m_length;
};

#endif /* PLANE_HPP_ */
