#include "scene_3d.hpp"
#include "bauasian/glsl/3d/globals.glsl"
#include "bauasian/primitives/scene_loader.hpp"
#include "bauasian/shaders/buffers/model_matrices_buffer.hpp"


using bauasian::Scene3D;
using bauasian::Entity3D;
using bauasian::Renderer;

Scene3D::Scene3D()
		: Scene()
{}

Scene3D::~Scene3D()
{
	for (auto& entity : m_entities)
		delete entity;

	for (auto& light : m_directional_lights)
		delete light;
	for (auto& light : m_point_lights)
		delete light;
	for (auto& light : m_spot_lights)
		delete light;
}

void bauasian::Scene3D::setCamera(Camera* camera)
{
	m_camera_ptr = camera;
}

void bauasian::Scene3D::addLight(DirectionalLight* directional_light)
{
	if (m_directional_lights.size() == MAX_DIR_LIGHTS)
		throw LightLimitReachedException("directional", MAX_DIR_LIGHTS);
	m_directional_lights.push_back(directional_light);
}

void bauasian::Scene3D::addLight(PointLight* point_light)
{
	if (m_directional_lights.size() == MAX_POINT_LIGHTS)
		throw LightLimitReachedException("point", MAX_POINT_LIGHTS);
	m_point_lights.push_back(point_light);
}

void bauasian::Scene3D::addLight(SpotLight* spot_light)
{
	if (m_directional_lights.size() == MAX_SPOT_LIGHTS)
		throw LightLimitReachedException("spot", MAX_SPOT_LIGHTS);
	m_spot_lights.push_back(spot_light);
}

void Scene3D::addEntity(Entity3D* entity)
{
	m_entities.push_back(entity);
}

void Scene3D::loadFromFile(const boost::filesystem::path& path, const bool& flip_uvs /* = false */)
{
	if (!boost::filesystem::exists(path))
		throw FileNotFoundException(path);

	SceneLoader* loader = new SceneLoader(path, flip_uvs);
	for (Mesh* mesh : loader->getMeshes())
		addEntity(mesh);
	delete loader;
}

void Scene3D::render(const ShaderProgram* shader, const glm::mat4& projection_matrix) const
{
	glEnable(GL_DEPTH_TEST);
	Scene::render(shader, projection_matrix);

	updateDirectionalLights(shader);
	updatePointLights(shader);
	updateSpotLights(shader);

	shader->setUniformVector3("camera_position", m_camera_ptr->getPosition());
	auto projection_view_matrix = projection_matrix * m_camera_ptr->getViewMatrix();
	for (auto& entity : m_entities)
	{
		const auto& buffer = ModelMatricesBuffer::getInstance();
		buffer.setProjectionViewMatrix(projection_view_matrix * entity->getModelMatrix());
		buffer.setModelMatrix(entity->getModelMatrix());
		buffer.setNormalMatrix(entity->getNormalMatrix());
		entity->render();
	}
}

void Scene3D::updateDirectionalLights(const ShaderProgram* shader) const
{
	for (unsigned i = 0; i < m_directional_lights.size(); i++)
	{
		auto i_str = std::to_string(i);
		shader->setUniformVector3("dir_lights[" + i_str + "].color", m_directional_lights[i]->getColor());
		shader->setUniformVector3("dir_lights[" + i_str + "].direction", m_directional_lights[i]->getDirection());
	}
	shader->setUniformInt("num_dir_lights", (unsigned) m_directional_lights.size());
}

void Scene3D::updatePointLights(const ShaderProgram* shader) const
{
	for (unsigned i = 0; i < m_point_lights.size(); i++)
	{
		auto i_str = std::to_string(i);
		shader->setUniformVector3("point_lights[" + i_str + "].color", m_point_lights[i]->getColor());
		shader->setUniformVector3("point_lights[" + i_str + "].position", m_point_lights[i]->getPosition());
		shader->setUniformFloat("point_lights[" + i_str + "].range", m_point_lights[i]->getRange());
	}
	shader->setUniformInt("num_point_lights", (unsigned) m_point_lights.size());
}

void Scene3D::updateSpotLights(const ShaderProgram* shader) const
{
	for (unsigned i = 0; i < m_spot_lights.size(); i++)
	{
		auto i_str = std::to_string(i);
		shader->setUniformVector3("spot_lights[" + i_str + "].color", m_spot_lights[i]->getColor());
		shader->setUniformVector3("spot_lights[" + i_str + "].position", m_spot_lights[i]->getPosition());
		shader->setUniformVector3("spot_lights[" + i_str + "].direction", m_spot_lights[i]->getDirection());
		shader->setUniformFloat("spot_lights[" + i_str + "].range", m_spot_lights[i]->getRange());
		shader->setUniformFloat("spot_lights[" + i_str + "].inner_angle", m_spot_lights[i]->getInnerAngle());
		shader->setUniformFloat("spot_lights[" + i_str + "].outer_angle", m_spot_lights[i]->getOuterAngle());
	}
	shader->setUniformInt("num_spot_lights", (unsigned) m_spot_lights.size());
}

const unsigned Scene3D::getNumVertices() const
{
	unsigned num_vertices = 0;
	for (const auto& entity : m_entities)
		num_vertices += entity->getNumVertices();
	return num_vertices;
}

const unsigned Scene3D::getNumFaces() const
{
	unsigned num_faces = 0;
	for (const auto& entity : m_entities)
		num_faces += entity->getNumFaces();
	return num_faces;
}

const unsigned Scene3D::getNumMeshes() const
{
	return (unsigned) m_entities.size();
}
