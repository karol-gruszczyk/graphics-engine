#ifndef SCENE_HPP_
#define SCENE_HPP_

#include <list>
#include <memory>
#include "renderer.hpp"


namespace engine
{
	class Scene;
}

class engine::Scene
{
public:
	Scene(Renderer* renderer);

	void setRenderer(Renderer* renderer);
	virtual void render() const;
protected:
	Renderer* m_renderer;

	ShaderProgram* getShaderProgram() const;
};

#endif /* SCENE_HPP_ */
