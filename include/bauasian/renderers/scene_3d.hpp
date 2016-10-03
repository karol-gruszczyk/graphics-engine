#ifndef BAUASIAN_SCENE_3D_HPP
#define BAUASIAN_SCENE_3D_HPP

#include <boost/filesystem.hpp>

#include "scene.hpp"
#include "bauasian/camera.hpp"
#include "bauasian/primitives/entities/entity_3d.hpp"
#include "bauasian/lights/directional_light.hpp"
#include "bauasian/lights/point_light.hpp"
#include "bauasian/lights/spot_light.hpp"
#include "bauasian/exceptions/light_limit_reached_exception.hpp"


namespace bauasian
{
	class Scene3D;
}

class bauasian::Scene3D : public Scene
{
public:
	Scene3D(Renderer* renderer);
	~Scene3D();

	void setCamera(Camera* camera);
	void addEntity(Entity3D* entity);
	void addLight(DirectionalLight* directional_light);
	void addLight(PointLight* point_light);
	void addLight(SpotLight* spot_light);
	void loadFromFile(const boost::filesystem::path& path);
	void render() const override;
private:
	Camera* m_camera_ptr;
	std::list<Entity3D*> m_entities;
	std::vector<DirectionalLight*> m_directional_lights;
	std::vector<PointLight*> m_point_lights;
	std::vector<SpotLight*> m_spot_lights;

	void updateDirectionalLights();
	void updatePointLights();
	void updateSpotLights();
};

#endif /* BAUASIAN_SCENE_3D_HPP */
