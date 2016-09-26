#ifndef SCENE_2D_HPP_
#define SCENE_2D_HPP_

#include "scene.hpp"
#include "../primitives/entities/entity_2d.hpp"


namespace engine
{
	class Scene2D;
}

class engine::Scene2D : public Scene
{
public:
	Scene2D(Renderer* renderer);

	void addEntity(Entity2D* entity);
	void render() const override;
private:
	std::list<Entity2D*> m_entities;
};

#endif /* SCENE_2D_HPP_ */
