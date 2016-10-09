#include "scene_2d.hpp"


using bauasian::Scene2D;
using bauasian::Entity2D;


Scene2D::~Scene2D()
{
	for (auto& entity : m_entities)
		delete entity;
}

void Scene2D::addEntity(Entity2D* entity)
{
	m_entities.push_back(entity);
}

void Scene2D::render(const ShaderProgram* shader, const GLint& model_matrix_location) const
{
	glDisable(GL_DEPTH_TEST);
	for (auto& entity : m_entities)
	{
		shader->setUniform(model_matrix_location, entity->getModelMatrix());
		entity->render();
	}
}
