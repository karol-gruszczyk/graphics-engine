#ifndef BAUASIAN_SCENE_HPP
#define BAUASIAN_SCENE_HPP

#include "renderer.hpp"


namespace bauasian
{
	class Scene;
}

class bauasian::Scene
{
public:
	Scene();

	virtual void render(const ShaderProgram* shader, const glm::mat4& projection_matrix) const;
protected:
};

#endif /* BAUASIAN_SCENE_HPP */
