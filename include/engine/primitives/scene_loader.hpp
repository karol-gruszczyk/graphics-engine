#ifndef MODEL_LOADER_HPP_
#define MODEL_LOADER_HPP_

#include <boost/filesystem/path.hpp>
#include <assimp/scene.h>
#include "mesh.hpp"
#include "../materials/material.hpp"


namespace engine
{
	class SceneLoader;
}

class engine::SceneLoader
{
public:
	SceneLoader(const boost::filesystem::path &path);

	const std::vector<Material *> &getMaterials();
	const std::vector<Mesh *> &getMeshes();
private:
	boost::filesystem::path m_directory;
	std::vector<Material *> m_materials;
	std::vector<Mesh *> m_meshes;

	Material *processMaterial(const aiMaterial *material);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh *processMesh(aiMesh *mesh);
	void processMaterials(const aiScene *scene);
};

#endif /* MODEL_LOADER_HPP_ */
