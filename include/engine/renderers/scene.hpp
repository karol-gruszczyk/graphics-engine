#ifndef GRAPHICS_ENGINE_SCENE_HPP
#define GRAPHICS_ENGINE_SCENE_HPP

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
	Scene(Renderer *renderer);

	void setRenderer(Renderer *renderer);
	virtual void render() const;
protected:
	Renderer *m_renderer;

	ShaderProgram *getShaderProgram() const;
};

#endif /* GRAPHICS_ENGINE_SCENE_HPP */
