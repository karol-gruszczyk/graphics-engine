#ifndef GRAPHICS_ENGINE_SCENE_3D_HPP
#define GRAPHICS_ENGINE_SCENE_3D_HPP

#include <boost/filesystem.hpp>

#include "scene.hpp"
#include "engine/camera.hpp"
#include "engine/primitives/entities/entity_3d.hpp"
#include "engine/lights/directional_light.hpp"
#include "engine/lights/point_light.hpp"
#include "engine/lights/spot_light.hpp"
#include "engine/exceptions/light_limit_reached_exception.hpp"


namespace engine
{
	class Scene3D;
}

class engine::Scene3D : public Scene
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
};

#endif /* GRAPHICS_ENGINE_SCENE_3D_HPP */
