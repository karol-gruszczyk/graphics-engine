#ifndef GRAPHICS_ENGINE_SCENE_2D_HPP
#define GRAPHICS_ENGINE_SCENE_2D_HPP

#include "scene.hpp"
#include "bauasian/primitives/entities/entity_2d.hpp"


namespace bauasian
{
	class Scene2D;
}

class bauasian::Scene2D : public Scene
{
public:
	Scene2D(Renderer* renderer);
	~Scene2D();

	void addEntity(Entity2D* entity);
	void render() const override;
private:
	std::list<Entity2D*> m_entities;
};

#endif /* GRAPHICS_ENGINE_SCENE_2D_HPP */
