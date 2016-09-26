#ifndef SCENE_3D_HPP_
#define SCENE_3D_HPP_

#include "scene.hpp"
#include "../camera.hpp"
#include "../primitives/entities/entity_3d.hpp"
#include "../lights/directional_light.hpp"
#include "../lights/point_light.hpp"
#include "../lights/spot_light.hpp"
#include "../exceptions/light_limit_reached_exception.hpp"


namespace engine
{
	class Scene3D;
}

class engine::Scene3D : public Scene
{
public:
	Scene3D(Renderer* renderer);

	void setCamera(Camera* camera);
	void addEntity(Entity3D* entity);
	void addLight(DirectionalLight* directional_light);
	void addLight(PointLight* point_light);
	void addLight(SpotLight* spot_light);
	void render() const override;
private:
	Camera* m_camera_ptr;
	std::list<Entity3D*> m_entities;
	std::vector<DirectionalLight*> m_directional_lights;
	std::vector<PointLight*> m_point_lights;
	std::vector<SpotLight*> m_spot_lights;
};

#endif /* SCENE_3D_HPP_ */
