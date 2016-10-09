#ifndef BAUASIAN_MODEL_LOADER_HPP
#define BAUASIAN_MODEL_LOADER_HPP

#include "mesh.hpp"
#include "bauasian/materials/material.hpp"
#include "bauasian/lights/directional_light.hpp"
#include "bauasian/lights/point_light.hpp"
#include "bauasian/lights/spot_light.hpp"

#include <assimp/scene.h>
#include <boost/filesystem/path.hpp>


namespace bauasian
{
	class SceneLoader;
}

class bauasian::SceneLoader final
{
public:
	SceneLoader(const boost::filesystem::path& path, const bool& flip_uvs = false);

	const std::list<Mesh*>& getMeshes() const;
	const std::list<DirectionalLight*>& getDirectionalLights() const;
	const std::list<PointLight*>& getPointLights() const;
	const std::list<SpotLight*>& getSpotLights() const;
private:
	boost::filesystem::path m_directory;
	std::vector<std::shared_ptr<Material>> m_materials;
	std::list<Mesh*> m_meshes;
	std::list<DirectionalLight*> m_directional_lights;
	std::list<PointLight*> m_point_lights;
	std::list<SpotLight*> m_spot_lights;

	void processMaterials(const aiScene* scene);
	std::shared_ptr<Material> processMaterial(const aiMaterial* material);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh* processMesh(aiMesh* mesh);
	void processLights(const aiScene* scene);
	const std::string getPath(const std::string& path);
};

#endif /* BAUASIAN_MODEL_LOADER_HPP */
