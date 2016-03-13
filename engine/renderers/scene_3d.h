#ifndef SCENE_3D_H_
#define SCENE_3D_H_

#include "scene.h"
#include "../camera.h"
#include "../primitives/entities/entity_3d.h"
#include "../lights/directional_light.h"


namespace engine
{
	class Scene3D;
}

class engine::Scene3D : public Scene
{
public:
	Scene3D();
	Scene3D(Renderer* renderer);

	void setCamera(Camera* camera);
	void addEntity(Entity3D* entity);
	void addLight(DirectionalLight* directional_light);
	void render() override;
private:
	Camera* m_camera_ptr;
	std::list<Entity3D*> m_entities;
	std::list<DirectionalLight*> m_directional_lights;
};

#endif /* SCENE_3D_H_ */
