#include "scene_3d.hpp"
#include "engine/glsl/3d/globals.glsl"
#include "engine/primitives/scene_loader.hpp"


using engine::Scene3D;
using engine::Entity3D;
using engine::Renderer;


Scene3D::Scene3D(Renderer *renderer)
		: Scene(renderer)
{}

Scene3D::~Scene3D()
{
	for (auto &entity : m_entities)
		delete entity;
}

void engine::Scene3D::setCamera(Camera *camera)
{
	m_camera_ptr = camera;
}

void engine::Scene3D::addLight(DirectionalLight *directional_light)
{
	if (m_directional_lights.size() == MAX_DIR_LIGHTS)
		throw LightLimitReachedException("directional", MAX_DIR_LIGHTS);
	m_directional_lights.push_back(directional_light);
}

void engine::Scene3D::addLight(PointLight *point_light)
{
	if (m_directional_lights.size() == MAX_POINT_LIGHTS)
		throw LightLimitReachedException("point", MAX_POINT_LIGHTS);
	m_point_lights.push_back(point_light);
}

void engine::Scene3D::addLight(SpotLight *spot_light)
{
	if (m_directional_lights.size() == MAX_SPOT_LIGHTS)
		throw LightLimitReachedException("spot", MAX_SPOT_LIGHTS);
	m_spot_lights.push_back(spot_light);
}

void Scene3D::addEntity(Entity3D *entity)
{
	m_entities.push_back(entity);
}

void Scene3D::loadFromFile(const boost::filesystem::path &path)
{
	if (!boost::filesystem::exists(path))
		throw FileNotFoundException(path);

	SceneLoader *loader = new SceneLoader(path);
	for (Mesh *mesh : loader->getMeshes())
		addEntity(mesh);
	delete loader;
}

void Scene3D::render() const
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	Scene::render();

	for (unsigned i = 0; i < m_directional_lights.size(); i++)
	{
		auto i_str = std::to_string(i);
		getShaderProgram()->setUniformVector3("dir_lights[" + i_str + "].color", m_directional_lights[i]->getColor());
		getShaderProgram()->setUniformVector3("dir_lights[" + i_str + "].direction",
		                                      m_directional_lights[i]->getDirection());
	}
	getShaderProgram()->setUniformUInt("num_dir_lights", (unsigned) m_point_lights.size());

	for (unsigned i = 0; i < m_point_lights.size(); i++)
	{
		auto i_str = std::to_string(i);
		getShaderProgram()->setUniformVector3("point_lights[" + i_str + "].color", m_point_lights[i]->getColor());
		getShaderProgram()->setUniformVector3("point_lights[" + i_str + "].position", m_point_lights[i]->getPosition());
		getShaderProgram()->setUniformFloat("point_lights[" + i_str + "].range", m_point_lights[i]->getRange());
	}
	getShaderProgram()->setUniformUInt("num_point_lights", (unsigned) m_point_lights.size());

	for (unsigned i = 0; i < m_spot_lights.size(); i++)
	{
		auto i_str = std::to_string(i);
		getShaderProgram()->setUniformVector3("spot_lights[" + i_str + "].color", m_spot_lights[i]->getColor());
		getShaderProgram()->setUniformVector3("spot_lights[" + i_str + "].position", m_spot_lights[i]->getPosition());
		getShaderProgram()->setUniformVector3("spot_lights[" + i_str + "].direction", m_spot_lights[i]->getDirection());
		getShaderProgram()->setUniformFloat("spot_lights[" + i_str + "].range", m_spot_lights[i]->getRange());
		getShaderProgram()->setUniformFloat("spot_lights[" + i_str + "].inner_angle",
		                                    m_spot_lights[i]->getInnerAngle());
		getShaderProgram()->setUniformFloat("spot_lights[" + i_str + "].outer_angle",
		                                    m_spot_lights[i]->getOuterAngle());
	}
	getShaderProgram()->setUniformUInt("num_spot_lights", (unsigned) m_spot_lights.size());

	getShaderProgram()->setUniformVector3("camera_position", m_camera_ptr->getPosition());
	auto projection_view_matrix = m_renderer->getProjectionMatrix() * m_camera_ptr->getViewMatrix();
	for (auto &entity : m_entities)
	{
		getShaderProgram()->setUniformMatrix4("projection_view_model_matrix",
		                                      projection_view_matrix * entity->getModelMatrix());
		getShaderProgram()->setUniformMatrix4("model_matrix", entity->getModelMatrix());
		getShaderProgram()->setUniformMatrix3("normal_matrix", entity->getNormalMatrix());
		entity->render();
	}
}
