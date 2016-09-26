#include "scene_loader.hpp"
#include "../config.hpp"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

using engine::SceneLoader;
using engine::Mesh;
using engine::Config;


SceneLoader::SceneLoader(const boost::filesystem::path& path)
{
	Assimp::Importer importer;
	auto post_process = aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices | aiProcess_RemoveRedundantMaterials;
	const aiScene* scene = importer.ReadFile(path.string(), post_process);

	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		Config::getInstance().log("Failed to open file(" + path.string() + "): " + importer.GetErrorString());
		return;
	}
	m_directory = path.parent_path();
	processNode(scene->mRootNode, scene);
}

SceneLoader::~SceneLoader()
{
	for (const auto& mesh : m_meshes)
		delete mesh;
}

const std::vector<Mesh*>& engine::SceneLoader::getMeshes()
{
	return m_meshes;
}

void SceneLoader::processNode(aiNode* node, const aiScene* scene)
{
	for (unsigned i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		m_meshes.push_back(processMesh(mesh, scene));
	}

	for (unsigned i = 0; i < node->mNumChildren; i++)
		processNode(node->mChildren[i], scene);
}

Mesh* SceneLoader::processMesh(aiMesh* mesh, const aiScene* scene)
{
	unsigned num_vertices(mesh->mNumVertices), num_indices(mesh->mNumFaces * 3);
	bool has_texture_coords = mesh->mTextureCoords[0] != nullptr;
	
	float* positions = new float[num_vertices * 3];
	float* normals = new float[num_vertices * 3];
	float* texture_coords = new float[num_vertices * 2];
	unsigned* indices = new unsigned[num_indices];


	for (unsigned i = 0; i < num_vertices; i++)
	{
		positions[i * 3] = mesh->mVertices[i].x;
		positions[i * 3 + 1] = mesh->mVertices[i].y;
		positions[i * 3 + 2] = mesh->mVertices[i].z;

		normals[i * 3] = mesh->mNormals[i].x;
		normals[i * 3 + 1] = mesh->mNormals[i].y;
		normals[i * 3 + 2] = mesh->mNormals[i].z;

		if (has_texture_coords)
		{
			texture_coords[i * 2] = mesh->mTextureCoords[0][i].x;
			texture_coords[i * 2 + 1] = mesh->mTextureCoords[0][i].y;
		}

		for (unsigned i = 0; i < mesh->mNumFaces; i++)
		{
			// meshes are triangulated, so faces will always have 3 indices
			const aiFace& face = mesh->mFaces[i];
			indices[i * 3] = face.mIndices[0];
			indices[i * 3 + 1] = face.mIndices[1];
			indices[i * 3 + 2] = face.mIndices[2];
		}
	}
	Mesh* result_mesh = new Mesh(num_vertices, positions, normals, texture_coords, num_indices, indices);
	delete[] positions;
	delete[] normals;
	delete[] texture_coords;
	delete[] indices;
	return result_mesh;
}
