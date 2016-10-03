#include "scene_2d.hpp"


using bauasian::Scene2D;
using bauasian::Entity2D;
using bauasian::Renderer;


Scene2D::Scene2D(Renderer* renderer)
		: Scene(renderer)
{}

Scene2D::~Scene2D()
{
	for (auto& entity : m_entities)
		delete entity;
}

void Scene2D::addEntity(Entity2D* entity)
{
	m_entities.push_back(entity);
}

void Scene2D::render() const
{
	Scene::render();
	glDisable(GL_DEPTH_TEST);
	for (auto& entity : m_entities)
	{
		getShaderProgram()->setUniformMatrix4("model_matrix", entity->getModelMatrix());
		entity->render();
	}
}
