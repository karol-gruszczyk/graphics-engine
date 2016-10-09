#include "scene_loader.hpp"
#include "bauasian/materials/texture_factory.hpp"
#include "bauasian/bauasian.hpp"

#include <chrono>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <iostream>


using bauasian::SceneLoader;
using bauasian::Material;
using bauasian::Mesh;
using bauasian::DirectionalLight;
using bauasian::PointLight;
using bauasian::SpotLight;

SceneLoader::SceneLoader(const boost::filesystem::path& path, const bool& flip_uvs /* = false */)
{
	using namespace std::chrono;

	Bauasian::getInstance().logInfo("Loading scene '" + boost::filesystem::canonical(path).string() + "'");
	auto loading_start_time = steady_clock::now();

	Assimp::Importer importer;
	unsigned flags = flip_uvs ? aiProcess_FlipUVs : 0;
	const aiScene* scene = importer.ReadFile(path.string(), aiProcessPreset_TargetRealtime_Fast | flags);

	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		Bauasian::getInstance().logError("Failed to open file(" + path.string() + "): " + importer.GetErrorString());
		return;
	}
	m_directory = path.parent_path();
	processMaterials(scene);
	processNode(scene->mRootNode, scene);
	processLights(scene);

	duration<double, std::milli> loading_time = steady_clock::now() - loading_start_time;
	Bauasian::getInstance().logInfo("Scene '" + boost::filesystem::canonical(path).string() + "' loaded in " +
	                                std::to_string(loading_time.count()) + " ms");
}

SceneLoader::~SceneLoader()
{
	for (auto& light : m_directional_lights)
		delete light;
	for (auto& light : m_point_lights)
		delete light;
	for (auto& light : m_spot_lights)
		delete light;
}

const std::list<Mesh*>& SceneLoader::getMeshes() const
{
	return m_meshes;
}

const std::list<DirectionalLight*>& SceneLoader::getDirectionalLights() const
{
	return m_directional_lights;
}

const std::list<PointLight*>& SceneLoader::getPointLights() const
{
	return m_point_lights;
}

const std::list<SpotLight*>& SceneLoader::getSpotLights() const
{
	return m_spot_lights;
}

void SceneLoader::processMaterials(const aiScene* scene)
{
	for (unsigned i = 0; i < scene->mNumMaterials; i++)
		m_materials.push_back(processMaterial(scene->mMaterials[i]));
}

std::shared_ptr<Material> SceneLoader::processMaterial(const aiMaterial* material)
{
	auto result_mat = std::make_shared<Material>();

	aiString tmp_string;
	aiColor3D tmp_color3d = { 0.f, 0.f, 0.f };
	material->Get(AI_MATKEY_NAME, tmp_string);
	result_mat->setName(tmp_string.C_Str());

	if (material->GetTexture(aiTextureType_AMBIENT, 0, &tmp_string) == AI_SUCCESS)
	{
		try
		{
			result_mat->setAmbient(TextureFactory::getInstance().getTexture(getPath(tmp_string.C_Str())));
		}
		catch (FileNotFoundException& e)
		{
			Bauasian::getInstance().logError(e.what());
		}
	}
	material->Get(AI_MATKEY_COLOR_AMBIENT, tmp_color3d);
	result_mat->setAmbient({ tmp_color3d.r, tmp_color3d.g, tmp_color3d.b });

	if (material->GetTexture(aiTextureType_DIFFUSE, 0, &tmp_string) == AI_SUCCESS)
	{
		try
		{
			result_mat->setDiffuse(TextureFactory::getInstance().getTexture(getPath(tmp_string.C_Str())));
		}
		catch (FileNotFoundException& e)
		{
			Bauasian::getInstance().logError(e.what());
		}
	}
	material->Get(AI_MATKEY_COLOR_DIFFUSE, tmp_color3d);
	result_mat->setDiffuse({ tmp_color3d.r, tmp_color3d.g, tmp_color3d.b });

	if (material->GetTexture(aiTextureType_SPECULAR, 0, &tmp_string) == AI_SUCCESS)
	{
		try
		{
			result_mat->setSpecular(TextureFactory::getInstance().getTexture(getPath(tmp_string.C_Str())));
		}
		catch (FileNotFoundException& e)
		{
			Bauasian::getInstance().logError(e.what());
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
	bool has_texture_coordinates = mesh->HasTextureCoords(0);
	const unsigned floats_per_vertex = 3 + 3 + 2;
	float* vertex_data = new float[num_vertices * floats_per_vertex];
	unsigned* indices = new unsigned[num_indices];


	for (unsigned i = 0; i < num_vertices; i++)
	{
		vertex_data[i * floats_per_vertex + 0] = mesh->mVertices[i].x;
		vertex_data[i * floats_per_vertex + 1] = mesh->mVertices[i].y;
		vertex_data[i * floats_per_vertex + 2] = mesh->mVertices[i].z;

		vertex_data[i * floats_per_vertex + 3] = mesh->mNormals[i].x;
		vertex_data[i * floats_per_vertex + 4] = mesh->mNormals[i].y;
		vertex_data[i * floats_per_vertex + 5] = mesh->mNormals[i].z;

		if (has_texture_coordinates)
		{
			vertex_data[i * floats_per_vertex + 6] = mesh->mTextureCoords[0][i].x;
			vertex_data[i * floats_per_vertex + 7] = mesh->mTextureCoords[0][i].y;
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
	Mesh* result_mesh = new Mesh(num_vertices, vertex_data, num_indices, indices);
	delete[] vertex_data;
	delete[] indices;
	result_mesh->setMaterial(m_materials[mesh->mMaterialIndex]);
	return result_mesh;
}

void SceneLoader::processLights(const aiScene* scene)
{
	for (auto i = 0; i < scene->mNumLights; i++)
	{
		const auto& light = scene->mLights[i];
		auto vec3 = [](const aiVector3D& x) -> const glm::vec3 { return glm::vec3(x.x, x.y, x.z); };
		auto col3 = [](const aiColor3D& x) -> const glm::vec3 { return glm::vec3(x.r, x.g, x.b); };
		if (light->mType == aiLightSource_DIRECTIONAL)
		{
			auto dir = new DirectionalLight(vec3(light->mDirection));
			dir->setColor(col3(light->mColorAmbient), col3(light->mColorDiffuse), col3(light->mColorSpecular));
			m_directional_lights.push_back(dir);
			break;
		}
		else if (light->mType == aiLightSource_POINT)
		{
			auto point = new PointLight(
					vec3(light->mPosition),
					{ light->mAttenuationConstant, light->mAttenuationLinear, light->mAttenuationQuadratic });
			point->setColor(col3(light->mColorAmbient), col3(light->mColorDiffuse), col3(light->mColorSpecular));
			m_point_lights.push_back(point);
		}
		else if (light->mType == aiLightSource_SPOT)
		{
			auto spot = new SpotLight(
					vec3(light->mPosition), vec3(light->mDirection),
					{ light->mAttenuationConstant, light->mAttenuationLinear, light->mAttenuationQuadratic },
					light->mAngleInnerCone, light->mAngleOuterCone);
			spot->setColor(col3(light->mColorAmbient), col3(light->mColorDiffuse), col3(light->mColorSpecular));
			m_point_lights.push_back(spot);
		}
	}
}

const std::string SceneLoader::getPath(const std::string& path)
{
	auto full_dir = (m_directory / path).string();
	std::replace(full_dir.begin(), full_dir.end(), '\\', '/');
	return full_dir;
}
