#ifndef SCENE_H_
#define SCENE_H_

#include <list>
#include <memory>
#include "../primitives/entities/entity.h"
#include "renderer.h"


namespace engine
{
	class Scene;
}

class engine::Scene abstract
{
public:
	Scene();
	Scene(Renderer* renderer);

	void setRenderer(Renderer* renderer);
	void addEntity(Entity* entity);
	void render();
private:
	Renderer* m_renderer;
	std::list<Entity*> m_entities;
};

#endif /* SCENE_H_ */
