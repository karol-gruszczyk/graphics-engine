#include "scene_3d.h"

using engine::Scene3D;
using engine::Entity3D;
using engine::Renderer;


Scene3D::Scene3D()
	: Scene()
{}

Scene3D::Scene3D(Renderer* renderer)
	: Scene(renderer)
{}

void engine::Scene3D::setCamera(Camera* camera)
{
	m_camera_ptr = camera;
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
	getShaderProgram()->setUniformMatrix4("view_matrix", m_camera_ptr->getViewMatrix());
	for (auto& entity : m_entities)
	{
		getShaderProgram()->setUniformMatrix4("model_matrix", entity->getModelMatrix());
		entity->render();
	}
}
