#ifndef GRAPHICS_ENGINE_BOX_HPP
#define GRAPHICS_ENGINE_BOX_HPP

#include "entities/entity_3d.hpp"


namespace engine
{
	class Box;
}

class engine::Box : public Entity3D
{
public:
	Box(const glm::vec3& size, const glm::vec3& position = { 0.f, 0.f, 0.f },
	    const glm::vec3& rotation = { 0.f, 0.f, 0.f }, const glm::vec3& scale = { 1.f, 1.f, 1.f },
	    const glm::vec3& pivot = { 0.f, 0.f, 0.f });
	void render() const override;

private:
	GLfloat m_width, m_length, m_height;
};

#endif /* GRAPHICS_ENGINE_BOX_HPP */
