#include "scene_2d.hpp"


using engine::Scene2D;
using engine::Entity2D;
using engine::Renderer;


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
	glDisable(GL_DEPTH_TEST);
	Scene::render();
	for (auto& entity : m_entities)
	{
		getShaderProgram()->setUniformMatrix4("model_matrix", entity->getModelMatrix());
		entity->render();
	}
}
