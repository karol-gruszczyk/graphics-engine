#include "scene_2d.hpp"


using bauasian::Scene2D;
using bauasian::Entity2D;
using bauasian::Renderer;


Scene2D::Scene2D()
		: Scene()
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

void Scene2D::render(const ShaderProgram* shader, const glm::mat4& projection_matrix) const
{
	Scene::render(shader, projection_matrix);
	glDisable(GL_DEPTH_TEST);
	for (auto& entity : m_entities)
	{
		shader->setUniformMatrix4("model_matrix", entity->getModelMatrix());
		entity->render();
	}
}
