#ifndef BAUASIAN_SCENE_3D_HPP
#define BAUASIAN_SCENE_3D_HPP

#include "scene.hpp"
#include "bauasian/camera.hpp"
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

class bauasian::Scene3D : public Scene
{
public:
	Scene3D();
	~Scene3D();

	void setCamera(Camera* camera);
	void addEntity(Entity3D* entity);
	void addLight(DirectionalLight* directional_light);
	void addLight(PointLight* point_light);
	void addLight(SpotLight* spot_light);
	void loadFromFile(const boost::filesystem::path& path, const bool& flip_uvs = false);
	const unsigned int getNumVertices() const;
	const unsigned int getNumFaces() const;
	const unsigned int getNumMeshes() const;
	void render(const ShaderProgram* shader, const glm::mat4& projection_matrix) const override;
private:
	Camera* m_camera_ptr;
	std::list<Entity3D*> m_entities;
	std::vector<DirectionalLight*> m_directional_lights;
	std::vector<PointLight*> m_point_lights;
	std::vector<SpotLight*> m_spot_lights;

	void updateDirectionalLights(const ShaderProgram* shader) const;
	void updatePointLights(const ShaderProgram* shader) const;
	void updateSpotLights(const ShaderProgram* shader) const;
};

#endif /* BAUASIAN_SCENE_3D_HPP */
