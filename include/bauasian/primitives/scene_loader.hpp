#ifndef BAUASIAN_MODEL_LOADER_HPP
#define BAUASIAN_MODEL_LOADER_HPP

#include "mesh.hpp"
#include "bauasian/materials/material.hpp"

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

	const std::vector<Mesh*>& getMeshes();
private:
	boost::filesystem::path m_directory;
	std::vector<std::shared_ptr<Material>> m_materials;
	std::vector<Mesh*> m_meshes;

	std::shared_ptr<Material> processMaterial(const aiMaterial* material);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh* processMesh(aiMesh* mesh);
	void processMaterials(const aiScene* scene);
	const std::string getPath(const std::string& path);
};

#endif /* BAUASIAN_MODEL_LOADER_HPP */
