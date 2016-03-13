#ifndef SCENE_2D_H_
#define SCENE_2D_H_

#include "scene.h"
#include "../primitives/entities/entity_2d.h"


namespace engine
{
	class Scene2D;
}

class engine::Scene2D : public Scene
{
public:
	Scene2D();
	Scene2D(Renderer* renderer);

	void addEntity(Entity2D* entity);
	void render() override;
private:
	std::list<Entity2D*> m_entities;
};

#endif /* SCENE_2D_H_ */
