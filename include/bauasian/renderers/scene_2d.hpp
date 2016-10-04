#ifndef BAUASIAN_SCENE_2D_HPP
#define BAUASIAN_SCENE_2D_HPP

#include "scene.hpp"
#include "bauasian/primitives/abstract/entity_2d.hpp"


namespace bauasian
{
	class Scene2D;
}

class bauasian::Scene2D : public Scene
{
public:
	Scene2D();
	~Scene2D();

	void addEntity(Entity2D* entity);
	void render(const ShaderProgram* shader, const glm::mat4& projection_matrix) const override;
private:
	std::list<Entity2D*> m_entities;
};

#endif /* BAUASIAN_SCENE_2D_HPP */
