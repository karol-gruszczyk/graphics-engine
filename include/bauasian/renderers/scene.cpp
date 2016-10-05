#include "scene.hpp"


using bauasian::Scene;
using bauasian::Renderer;
using bauasian::ShaderProgram;


Scene::Scene()
{}

void Scene::render(const ShaderProgram* shader, const glm::mat4& projection_matrix) const
{
	shader->use();
}
