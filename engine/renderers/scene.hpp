#ifndef SCENE_HPP_
#define SCENE_HPP_

#include <list>
#include <memory>
#include "renderer.hpp"


namespace engine
{
	class Scene;
}

class engine::Scene abstract
{
public:
	Scene(Renderer* renderer);

	void setRenderer(Renderer* renderer);
	virtual void render();
protected:
	Renderer* m_renderer;

	ShaderProgram* getShaderProgram();
};

#endif /* SCENE_HPP_ */
