#include "scene.hpp"

using engine::Scene;
using engine::Renderer;
using engine::ShaderProgram;


Scene::Scene(Renderer* renderer)
{
	setRenderer(renderer);
}

void Scene::setRenderer(Renderer* renderer)
{
	m_renderer = renderer;
}

void Scene::render()
{
	m_renderer->m_shader_program->bind();
}

ShaderProgram* Scene::getShaderProgram()
{
	return m_renderer->m_shader_program.get();
}
