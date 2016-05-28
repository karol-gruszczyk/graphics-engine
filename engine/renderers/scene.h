#ifndef SCENE_H_
#define SCENE_H_

#include <list>
#include <memory>
#include "renderer.h"


namespace engine
{
	class Scene;
}

class engine::Scene abstract
{
public:
	Scene();
	Scene(Renderer* renderer);

	void setRenderer(Renderer* renderer);
	virtual void render();
protected:
	Renderer* m_renderer;

	ShaderProgram* getShaderProgram();
};

#endif /* SCENE_H_ */
