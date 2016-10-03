#ifndef BAUASIAN_MODEL_LOADER_HPP
#define BAUASIAN_MODEL_LOADER_HPP

#include <boost/filesystem/path.hpp>
#include <assimp/scene.h>
#include "mesh.hpp"
#include "bauasian/materials/material.hpp"


namespace bauasian
{
	class SceneLoader;
}

class bauasian::SceneLoader final
{
public:
	SceneLoader(const boost::filesystem::path& path);

	const std::vector<Material*>& getMaterials();
	const std::vector<Mesh*>& getMeshes();
private:
	boost::filesystem::path m_directory;
	std::vector<Material*> m_materials;
	std::vector<Mesh*> m_meshes;

	Material* processMaterial(const aiMaterial* material);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh* processMesh(aiMesh* mesh);
	void processMaterials(const aiScene* scene);
};

#endif /* BAUASIAN_MODEL_LOADER_HPP */
