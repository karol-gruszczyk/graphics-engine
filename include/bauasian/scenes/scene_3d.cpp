#include "scene_3d.hpp"
#include "bauasian/glsl/3d/globals.glsl"
#include "scene_loader.hpp"
#include "bauasian/shaders/buffers/model_matrices_buffer.hpp"
#include "bauasian/shaders/buffers/scene_buffer.hpp"


using bauasian::Scene3D;
using bauasian::Entity3D;
using bauasian::Camera;

Scene3D::~Scene3D()
{
	for (auto& entity : m_entities)
		delete entity;
}

Camera* Scene3D::getCamera()
{
	return m_current_camera;
}

void Scene3D::setCamera(Camera* camera)
{
	m_current_camera = camera;
}

Camera* Scene3D::addCamera(const Camera& camera)
{
	m_cameras.push_back(camera);
	if (!m_current_camera)
		setCamera(&m_cameras.front());
	return &m_cameras.front();
}

void Scene3D::addLight(const DirectionalLight& directional_light)
{
	if (m_directional_lights.size() == MAX_DIR_LIGHTS)
		throw LightLimitReachedException("directional", MAX_DIR_LIGHTS);
	m_directional_lights.push_back(directional_light);
	m_num_lights[0] = (unsigned) m_directional_lights.size();
}

void Scene3D::addLight(const PointLight& point_light)
{
	if (m_directional_lights.size() == MAX_POINT_LIGHTS)
		throw LightLimitReachedException("point", MAX_POINT_LIGHTS);
	m_point_lights.push_back(point_light);
	m_num_lights[1] = (unsigned) m_point_lights.size();
}

void Scene3D::addLight(const SpotLight& spot_light)
{
	if (m_directional_lights.size() == MAX_SPOT_LIGHTS)
		throw LightLimitReachedException("spot", MAX_SPOT_LIGHTS);
	m_spot_lights.push_back(spot_light);
	m_num_lights[2] = (unsigned) m_spot_lights.size();
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
	for (auto mesh : loader->getMeshes())
		addEntity(mesh);
	for (auto camera : loader->getCameras())
		addCamera(*camera);
	for (auto light : loader->getDirectionalLights())
		addLight(*light);
	for (auto light : loader->getPointLights())
		addLight(*light);
	for (auto light : loader->getSpotLights())
		addLight(*light);
	delete loader;
}

void Scene3D::render(const glm::mat4& projection_matrix) const
{
	glEnable(GL_DEPTH_TEST);

	SceneBuffer::getInstance().setDirectionalLights(&m_directional_lights[0], m_num_lights[0]);
	SceneBuffer::getInstance().setPointLights(&m_point_lights[0], m_num_lights[1]);
	SceneBuffer::getInstance().setSpotLights(&m_spot_lights[0], m_num_lights[2]);
	SceneBuffer::getInstance().setCameraPosition(m_current_camera->getPosition());
	SceneBuffer::getInstance().setNumLights(m_num_lights);
	auto projection_view_matrix = projection_matrix * m_current_camera->getViewMatrix();
	for (auto& entity : m_entities)
	{
		const auto& buffer = ModelMatricesBuffer::getInstance();
		buffer.setProjectionViewMatrix(projection_view_matrix * entity->getModelMatrix());
		buffer.setModelMatrix(entity->getModelMatrix());
		buffer.setNormalMatrix(entity->getNormalMatrix());
		entity->render();
	}
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
