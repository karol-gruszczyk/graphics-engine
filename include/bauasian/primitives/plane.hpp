#ifndef BAUASIAN_PLANE_HPP
#define BAUASIAN_PLANE_HPP

#include "entities/entity_3d.hpp"


namespace bauasian
{
	class Plane;
}

class bauasian::Plane : public Entity3D
{
public:
	Plane(const glm::vec2& size, const glm::vec3& position = { 0.f, 0.f, 0.f }, const unsigned& tile = 1,
	      const glm::vec3& rotation = { 0.f, 0.f, 0.f },
	      const glm::vec3& scale = { 1.f, 1.f, 1.f }, const glm::vec3& pivot = { 0.f, 0.f, 0.f });

private:
	GLfloat m_width, m_length;
};

#endif /* BAUASIAN_PLANE_HPP */
