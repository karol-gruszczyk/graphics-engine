#ifndef BAUASIAN_SCENE_3D_HPP
#define BAUASIAN_SCENE_3D_HPP

#include "camera.hpp"
#include "sky_box.hpp"
#include "bauasian/primitives/abstract/entity_3d.hpp"
#include "bauasian/lights/directional_light.hpp"
#include "bauasian/lights/point_light.hpp"
#include "bauasian/lights/spot_light.hpp"
#include "bauasian/exceptions/light_limit_reached_exception.hpp"

#include <boost/filesystem.hpp>


namespace bauasian
{
	class Scene3D;
}

class bauasian::Scene3D
{
public:
	Scene3D(SkyBox* sky_box = nullptr);
	~Scene3D();

	Camera* getCamera();
	void setCamera(Camera* camera);
	void addCamera(Camera* camera);
	void addEntity(Entity3D* entity);
	void addLight(const DirectionalLight& directional_light);
	void addLight(const PointLight& point_light);
	void addLight(const SpotLight& spot_light);
	void loadFromFile(const boost::filesystem::path& path, const bool& flip_uvs = false,
	                  const bool& map_bump_to_normal = false);
	const unsigned int getNumVertices() const;
	const unsigned int getNumFaces() const;
	const unsigned int getNumMeshes() const;
	void render(const glm::mat4& projection_matrix) const;

private:
	SkyBox* m_sky_box;
	Camera* m_current_camera = nullptr;
	std::vector<Camera*> m_cameras;
	std::list<Entity3D*> m_entities;
	std::vector<DirectionalLight> m_directional_lights;
	std::vector<PointLight> m_point_lights;
	std::vector<SpotLight> m_spot_lights;
	unsigned m_num_lights[3] = { 0, 0, 0 };

};

#endif /* BAUASIAN_SCENE_3D_HPP */
