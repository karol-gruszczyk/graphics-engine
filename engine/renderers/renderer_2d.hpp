#ifndef RENDERER_2D_HPP_
#define RENDERER_2D_HPP_

#include "renderer.hpp"


namespace engine
{
	class Renderer2D;
}

class engine::Renderer2D : public Renderer
{
public:
	Renderer2D(unsigned context_width, unsigned context_height);

	void setContextWidth(unsigned context_width, unsigned context_height);
protected:
	void updateProjectionMatrix() override;
	void loadShader();
};

#endif /* RENDERER_2D_HPP_ */
