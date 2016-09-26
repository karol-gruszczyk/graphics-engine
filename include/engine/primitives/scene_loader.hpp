#ifndef MODEL_LOADER_HPP_
#define MODEL_LOADER_HPP_

#include <boost/filesystem/path.hpp>
#include <assimp/scene.h>
#include "mesh.hpp"


namespace engine
{
	class SceneLoader;
}

class engine::SceneLoader
{
public:
	SceneLoader(const boost::filesystem::path& path);

	const std::vector<engine::Mesh*>& getMeshes();
private:
	boost::filesystem::path m_directory;
	std::vector<engine::Mesh*> m_meshes;

	void processNode(aiNode* node, const aiScene* scene);
	Mesh* processMesh(aiMesh* mesh, const aiScene* scene);
};

#endif /* MODEL_LOADER_HPP_ */
