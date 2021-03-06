#include "scene_3d.hpp"
#include "scene_loader.hpp"


using bauasian::Scene3D;
using bauasian::Entity3D;
using bauasian::Camera;
using bauasian::DirectionalLight;
using bauasian::PointLight;
using bauasian::SpotLight;

Scene3D::Scene3D(SkyBox* sky_box)
		: m_sky_box(sky_box)
{}

Scene3D::~Scene3D()
{
	for (auto& entity : m_entities)
		delete entity;
	for (auto& camera : m_cameras)
		delete camera;
}

void Scene3D::addCamera(Camera* camera)
{
	m_cameras.push_back(camera);
	if (!m_current_camera)
		setCamera(m_cameras.front());
}

void Scene3D::addEntity(Entity3D* entity)
{
	m_entities.push_back(entity);
}

void Scene3D::addLight(DirectionalLight* directional_light)
{
	m_directional_lights.push_back(directional_light);
}

void Scene3D::addLight(PointLight* point_light)
{
	m_point_lights.push_back(point_light);
}

void Scene3D::addLight(SpotLight* spot_light)
{
	m_spot_lights.push_back(spot_light);
}

void Scene3D::loadFromFile(const boost::filesystem::path& path, bool flip_uvs, bool map_bump_to_normal)
{
	if (!boost::filesystem::exists(path))
		throw FileNotFoundException(path);

	SceneLoader* loader = new SceneLoader(path, flip_uvs, map_bump_to_normal);
	for (auto mesh : loader->getMeshes())
		addEntity(mesh);
	for (auto camera : loader->getCameras())
		addCamera(camera);
	for (auto light : loader->getDirectionalLights())
		addLight(light);
	for (auto light : loader->getPointLights())
		addLight(light);
	for (auto light : loader->getSpotLights())
		addLight(light);
	delete loader;
}

void Scene3D::render() const
{
	m_current_camera->bind();
	for (auto& entity : m_entities)
		entity->render();
}

unsigned Scene3D::getNumVertices() const
{
	unsigned num_vertices = 0;
	for (const auto& entity : m_entities)
		num_vertices += entity->getNumVertices();
	return num_vertices;
}

unsigned Scene3D::getNumFaces() const
{
	unsigned num_faces = 0;
	for (const auto& entity : m_entities)
		num_faces += entity->getNumFaces();
	return num_faces;
}

void Scene3D::renderSkyBox() const
{
	m_sky_box->render(m_current_camera->getProjectionMatrix() * glm::mat4(glm::mat3(m_current_camera->getViewMatrix())));
}
