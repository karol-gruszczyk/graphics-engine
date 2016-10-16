#include "scene_loader.hpp"
#include "bauasian/materials/texture_factory.hpp"
#include "bauasian/bauasian.hpp"

#include <chrono>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <glm/gtc/matrix_transform.hpp>


using bauasian::SceneLoader;
using bauasian::Material;
using bauasian::Mesh;
using bauasian::Camera;
using bauasian::DirectionalLight;
using bauasian::PointLight;
using bauasian::SpotLight;
using bauasian::Texture;

SceneLoader::SceneLoader(const boost::filesystem::path& path, const bool& flip_uvs,
                         const bool& map_bump_to_normal)
		: m_normal_map(map_bump_to_normal ? aiTextureType_HEIGHT : aiTextureType_NORMALS)
{
	using namespace std::chrono;

	Bauasian::getInstance().logInfo("Loading scene '" + boost::filesystem::canonical(path).string() + "'");
	auto loading_start_time = steady_clock::now();

	Assimp::Importer importer;
	unsigned flags = (flip_uvs ? aiProcess_FlipUVs : 0U);
	const aiScene* scene = importer.ReadFile(path.string(), aiProcessPreset_TargetRealtime_Fast | flags);

	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		Bauasian::getInstance().logError("Failed to open file(" + path.string() + "): " + importer.GetErrorString());
		return;
	}
	m_directory = path.parent_path();
	processMaterials(scene);
	processNode(scene->mRootNode, scene, glm::mat4());
	processCameras(scene);
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

const std::list<Camera*>& SceneLoader::getCameras() const
{
	return m_cameras;
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

const glm::vec3 SceneLoader::to_vec(const aiVector3D& v)
{
	return glm::vec3(v.x, v.y, v.z);
}

const glm::vec3 SceneLoader::to_vec(const aiColor3D& v)
{
	return glm::vec3(v.r, v.g, v.b);
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
		result_mat->setAmbient(getTexture(tmp_string, true));
	material->Get(AI_MATKEY_COLOR_AMBIENT, tmp_color3d);
	result_mat->setAmbient({ tmp_color3d.r, tmp_color3d.g, tmp_color3d.b });

	if (material->GetTexture(aiTextureType_DIFFUSE, 0, &tmp_string) == AI_SUCCESS)
		result_mat->setDiffuse(getTexture(tmp_string, true));
	material->Get(AI_MATKEY_COLOR_DIFFUSE, tmp_color3d);
	result_mat->setDiffuse({ tmp_color3d.r, tmp_color3d.g, tmp_color3d.b });

	if (material->GetTexture(aiTextureType_SPECULAR, 0, &tmp_string) == AI_SUCCESS)
		result_mat->setSpecular(getTexture(tmp_string, false));
	material->Get(AI_MATKEY_COLOR_SPECULAR, tmp_color3d);
	result_mat->setSpecular({ tmp_color3d.r, tmp_color3d.g, tmp_color3d.b });

	if (material->GetTexture(m_normal_map, 0, &tmp_string) == AI_SUCCESS)
		result_mat->setNormalTexture(getTexture(tmp_string, false));

	if (material->GetTexture(aiTextureType_OPACITY, 0, &tmp_string) == AI_SUCCESS)
		result_mat->setOpacityTexture(getTexture(tmp_string, false));

	float shininess = 0.f;
	material->Get(AI_MATKEY_SHININESS, shininess);
	result_mat->setShininess(shininess);

	return result_mat;
}

void SceneLoader::processNode(aiNode* node, const aiScene* scene, const glm::mat4& parent_matrix)
{
	const auto& mat = node->mTransformation;
	const glm::mat4 node_matrix(mat.a1, mat.b1, mat.c1, mat.d1,
	                            mat.a2, mat.b2, mat.c2, mat.d2,
	                            mat.a3, mat.b3, mat.c3, mat.d3,
	                            mat.a4, mat.b4, mat.c4, mat.d4);
	const glm::mat4 model_matrix = node_matrix * parent_matrix;
	for (unsigned i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		auto processed_mesh = processMesh(mesh);
		processed_mesh->setName(node->mName.C_Str());
		processed_mesh->setModelMatrix(model_matrix);
		m_meshes.push_back(processed_mesh);
	}

	for (unsigned i = 0; i < node->mNumChildren; i++)
		processNode(node->mChildren[i], scene, model_matrix);
}

Mesh* SceneLoader::processMesh(aiMesh* mesh)
{
	unsigned num_vertices(mesh->mNumVertices), num_indices(mesh->mNumFaces * 3);
	bool has_texture_coordinates = mesh->HasTextureCoords(0);
	bool has_tangents = mesh->HasTangentsAndBitangents();
	Entity3D::Vertex3D* vertex_data = new Entity3D::Vertex3D[num_vertices];
	unsigned* indices = new unsigned[num_indices];

	for (unsigned i = 0; i < num_vertices; i++)
	{
		vertex_data[i].position = to_vec(mesh->mVertices[i]);
		vertex_data[i].normal = to_vec(mesh->mNormals[i]);

		if (has_texture_coordinates)
		{
			vertex_data[i].uv.x = mesh->mTextureCoords[0][i].x;
			vertex_data[i].uv.y = mesh->mTextureCoords[0][i].y;
		}

		if (has_tangents)
		{
			vertex_data[i].tangent = to_vec(mesh->mTangents[i]);
			vertex_data[i].bi_tangent = to_vec(mesh->mBitangents[i]);
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

void SceneLoader::processCameras(const aiScene* scene)
{
	for (unsigned i = 0; i < scene->mNumCameras; i++)
	{
		const auto& camera = scene->mCameras[i];
		glm::mat4 view_matrix = glm::lookAt(to_vec(camera->mPosition), to_vec(camera->mLookAt), to_vec(camera->mUp));
		auto cam = new Camera(view_matrix);
		cam->setName(camera->mName.C_Str());
		m_cameras.push_back(cam);
	}
}

void SceneLoader::processLights(const aiScene* scene)
{
	for (unsigned i = 0; i < scene->mNumLights; i++)
	{
		const auto& light = scene->mLights[i];
		if (light->mType == aiLightSource_DIRECTIONAL)
		{
			auto dir = new DirectionalLight(to_vec(light->mDirection));
			dir->setColor(to_vec(light->mColorAmbient), to_vec(light->mColorDiffuse), to_vec(light->mColorSpecular));
			m_directional_lights.push_back(dir);
			break;
		}
		else if (light->mType == aiLightSource_POINT)
		{
			auto point = new PointLight(
					to_vec(light->mPosition),
					{ light->mAttenuationConstant, light->mAttenuationLinear, light->mAttenuationQuadratic });
			point->setColor(to_vec(light->mColorAmbient), to_vec(light->mColorDiffuse), to_vec(light->mColorSpecular));
			m_point_lights.push_back(point);
		}
		else if (light->mType == aiLightSource_SPOT)
		{
			auto spot = new SpotLight(
					to_vec(light->mPosition), to_vec(light->mDirection),
					{ light->mAttenuationConstant, light->mAttenuationLinear, light->mAttenuationQuadratic },
					light->mAngleInnerCone, light->mAngleOuterCone);
			spot->setColor(to_vec(light->mColorAmbient), to_vec(light->mColorDiffuse), to_vec(light->mColorSpecular));
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

Texture* SceneLoader::getTexture(const aiString& path, const bool& is_standardized)
{
	try
	{
		return TextureFactory::getInstance().getTexture(getPath(path.C_Str()), is_standardized);
	}
	catch (FileNotFoundException& e)
	{
		Bauasian::getInstance().logError(e.what());
	}
	return nullptr;
}
