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
	Renderer2D(const unsigned &context_width, const unsigned &context_height);

	virtual void setContextWidth(const unsigned &context_width, const unsigned &context_height) override;
protected:
	void updateProjectionMatrix() override;
	void loadShader();
};

#endif /* RENDERER_2D_HPP_ */
