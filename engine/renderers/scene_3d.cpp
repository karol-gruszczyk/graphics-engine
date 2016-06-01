#include "scene_3d.h"

using engine::Scene3D;
using engine::Entity3D;
using engine::Renderer;


Scene3D::Scene3D(Renderer* renderer)
	: Scene(renderer)
{}

void engine::Scene3D::setCamera(Camera* camera)
{
	m_camera_ptr = camera;
}

void engine::Scene3D::addLight(DirectionalLight* directional_light)
{
	m_directional_lights.push_back(directional_light);
}

void engine::Scene3D::addLight(PointLight* point_light)
{
	m_point_lights.push_back(point_light);
}

void engine::Scene3D::addLight(SpotLight* spot_light)
{
	m_spot_lights.push_back(spot_light);
}

void Scene3D::addEntity(Entity3D* entity)
{
	m_entities.push_back(entity);
}

void Scene3D::render()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	Scene::render();
	
	for (unsigned i = 0; i < m_directional_lights.size(); i++)
	{
		auto i_str = std::to_string(i);
		getShaderProgram()->setUniformVector3("dir_lights[" + i_str + "].color", m_directional_lights[i]->getColor());
		getShaderProgram()->setUniformVector3("dir_lights[" + i_str + "].direction", m_directional_lights[i]->getDirection());
	}
	getShaderProgram()->setUniformUint("num_dir_lights", m_point_lights.size());

	for (unsigned i = 0; i < m_point_lights.size(); i++)
	{
		auto i_str = std::to_string(i);
		getShaderProgram()->setUniformVector3("point_lights[" + i_str + "].color", m_point_lights[i]->getColor());
		getShaderProgram()->setUniformVector3("point_lights[" + i_str + "].position", m_point_lights[i]->getPosition());
		getShaderProgram()->setUniformFloat("point_lights[" + i_str + "].range", m_point_lights[i]->getRange());
	}
	getShaderProgram()->setUniformUint("num_point_lights", m_point_lights.size());

	for (unsigned i = 0; i < m_spot_lights.size(); i++)
	{
		auto i_str = std::to_string(i);
		getShaderProgram()->setUniformVector3("spot_lights[" + i_str + "].color", m_spot_lights[i]->getColor());
		getShaderProgram()->setUniformVector3("spot_lights[" + i_str + "].position", m_spot_lights[i]->getPosition());
		getShaderProgram()->setUniformVector3("spot_lights[" + i_str + "].direction", m_spot_lights[i]->getDirection());
		getShaderProgram()->setUniformFloat("spot_lights[" + i_str + "].range", m_spot_lights[i]->getRange());
		getShaderProgram()->setUniformFloat("spot_lights[" + i_str + "].inner_angle", m_spot_lights[i]->getInnerAngle());
		getShaderProgram()->setUniformFloat("spot_lights[" + i_str + "].outer_angle", m_spot_lights[i]->getOuterAngle());
	}
	getShaderProgram()->setUniformUint("num_spot_lights", m_spot_lights.size());
	
	getShaderProgram()->setUniformVector3("camera_position", m_camera_ptr->getPosition());
	getShaderProgram()->setUniformMatrix4("view_matrix", m_camera_ptr->getViewMatrix());
	for (auto& entity : m_entities)
	{
		getShaderProgram()->setUniformMatrix4("model_matrix", entity->getModelMatrix());
		entity->render();
	}
}
