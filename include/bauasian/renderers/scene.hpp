#ifndef BAUASIAN_SCENE_HPP
#define BAUASIAN_SCENE_HPP

#include <list>
#include <memory>
#include "renderer.hpp"


namespace bauasian
{
	class Scene;
}

class bauasian::Scene
{
public:
	Scene(Renderer* renderer);

	void setRenderer(Renderer* renderer);
	virtual void render() const;
protected:
	Renderer* m_renderer;

	ShaderProgram* getShaderProgram() const;
};

#endif /* BAUASIAN_SCENE_HPP */
