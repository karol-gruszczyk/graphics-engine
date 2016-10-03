#include "scene.hpp"


using bauasian::Scene;
using bauasian::Renderer;
using bauasian::ShaderProgram;


Scene::Scene(Renderer* renderer)
{
	setRenderer(renderer);
}

void Scene::setRenderer(Renderer* renderer)
{
	m_renderer = renderer;
}

void Scene::render() const
{
	m_renderer->m_shader_program->bind();
}

ShaderProgram* Scene::getShaderProgram() const
{
	return m_renderer->m_shader_program;
}
