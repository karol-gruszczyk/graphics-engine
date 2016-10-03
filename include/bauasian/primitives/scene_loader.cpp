#include "scene_loader.hpp"
#include "bauasian/engine.hpp"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <chrono>


using bauasian::SceneLoader;
using bauasian::Material;
using bauasian::Mesh;
using bauasian::Engine;

SceneLoader::SceneLoader(const boost::filesystem::path& path)
{
	using namespace std::chrono;

	Engine::getInstance().logInfo("Loading scene '" + boost::filesystem::canonical(path).string() + "'");
	auto loading_start_time = steady_clock::now();

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path.string(), aiProcessPreset_TargetRealtime_Fast);

	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		Engine::getInstance().logError("Failed to open file(" + path.string() + "): " + importer.GetErrorString());
		return;
	}
	m_directory = path.parent_path();
	processMaterials(scene);
	processNode(scene->mRootNode, scene);

	duration<double, std::milli> loading_time = steady_clock::now() - loading_start_time;
	Engine::getInstance().logInfo("Scene '" + boost::filesystem::canonical(path).string() + "' loaded in " +
	                              std::to_string(loading_time.count()) + " ms");
}

const std::vector<Material*>& SceneLoader::getMaterials()
{
	return m_materials;
}

const std::vector<Mesh*>& SceneLoader::getMeshes()
{
	return m_meshes;
}

void SceneLoader::processMaterials(const aiScene* scene)
{
	for (unsigned i = 0; i < scene->mNumMaterials; i++)
		m_materials.push_back(processMaterial(scene->mMaterials[i]));
}

Material* SceneLoader::processMaterial(const aiMaterial* material)
{
	Material* result_mat = new Material();

	aiString tmp_string;
	aiColor3D tmp_color3d = { 0.f, 0.f, 0.f };
	float ai_float = 0;
	material->Get(AI_MATKEY_NAME, tmp_string);
	result_mat->setName(tmp_string.C_Str());

	if (material->GetTexture(aiTextureType_AMBIENT, 0, &tmp_string) == AI_SUCCESS)
	{
		try
		{
			result_mat->setAmbient(Texture::loadFromFile(m_directory / tmp_string.C_Str()));
		}
		catch (FileNotFoundException& e)
		{
			Engine::getInstance().logError(e.what());
		}
	}
	material->Get(AI_MATKEY_COLOR_AMBIENT, tmp_color3d);
	result_mat->setAmbient({ tmp_color3d.r, tmp_color3d.g, tmp_color3d.b });

	if (material->GetTexture(aiTextureType_DIFFUSE, 0, &tmp_string) == AI_SUCCESS)
	{
		try
		{
			result_mat->setDiffuse(Texture::loadFromFile(m_directory / tmp_string.C_Str()));
		}
		catch (FileNotFoundException& e)
		{
			Engine::getInstance().logError(e.what());
		}
	}
	material->Get(AI_MATKEY_COLOR_DIFFUSE, tmp_color3d);
	result_mat->setDiffuse({ tmp_color3d.r, tmp_color3d.g, tmp_color3d.b });

	if (material->GetTexture(aiTextureType_SPECULAR, 0, &tmp_string) == AI_SUCCESS)
	{
		try
		{
			result_mat->setSpecular(Texture::loadFromFile(m_directory / tmp_string.C_Str()));
		}
		catch (FileNotFoundException& e)
		{
			Engine::getInstance().logError(e.what());
		}
	}
	material->Get(AI_MATKEY_COLOR_SPECULAR, tmp_color3d);
	result_mat->setSpecular({ tmp_color3d.r, tmp_color3d.g, tmp_color3d.b });

	float shininess = 0.f;
	material->Get(AI_MATKEY_SHININESS, shininess);
	result_mat->setShininess(shininess);

	return result_mat;
}

void SceneLoader::processNode(aiNode* node, const aiScene* scene)
{
	for (unsigned i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		m_meshes.push_back(processMesh(mesh));
	}

	for (unsigned i = 0; i < node->mNumChildren; i++)
		processNode(node->mChildren[i], scene);
}

Mesh* SceneLoader::processMesh(aiMesh* mesh)
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
	}
	for (unsigned i = 0; i < mesh->mNumFaces; i++)
	{
		// meshes are triangulated, so faces will always have 3 indices
		const aiFace& face = mesh->mFaces[i];
		indices[i * 3] = face.mIndices[0];
		indices[i * 3 + 1] = face.mIndices[1];
		indices[i * 3 + 2] = face.mIndices[2];
	}
	Mesh* result_mesh = new Mesh(num_vertices, positions, normals, texture_coords, num_indices, indices);
	delete[] positions;
	delete[] normals;
	delete[] texture_coords;
	delete[] indices;
	result_mesh->setMaterial(m_materials[mesh->mMaterialIndex]);
	return result_mesh;
}