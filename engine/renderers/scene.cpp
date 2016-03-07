#include "scene.h"

using engine::Scene;
using engine::Renderer;
using engine::Entity;


Scene::Scene()
{}

Scene::Scene(Renderer* renderer)
{
	setRenderer(renderer);
}

void Scene::setRenderer(Renderer* renderer)
{
	m_renderer = renderer;
}

void Scene::addEntity(Entity* entity)
{
	m_entities.push_back(entity);
	entity->m_shaders.push_back(m_renderer->m_shader_program.get());
	entity->updateModelMatrix();
}

void Scene::render()
{
	m_renderer->m_shader_program->bind();
	for (auto& entity : m_entities)
		entity->render();
}
