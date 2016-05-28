#ifndef RENDERER_2D_H_
#define RENDERER_2D_H_

#include "renderer.h"


namespace engine
{
	class Renderer2D;
}

class engine::Renderer2D : public Renderer
{
public:
	Renderer2D();
	Renderer2D(unsigned context_width, unsigned context_height);

	void setContextWidth(unsigned context_width, unsigned context_height);
protected:
	void updateProjectionMatrix() override;
	void loadDefaultShader() override;
};

#endif /* RENDERER_2D_H_ */
