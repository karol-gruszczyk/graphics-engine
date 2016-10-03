#ifndef GRAPHICS_ENGINE_RENDERER_2D_HPP
#define GRAPHICS_ENGINE_RENDERER_2D_HPP

#include "renderer.hpp"
#include "bauasian/context_width_interface.hpp"


namespace bauasian
{
	class Renderer2D;
}

class bauasian::Renderer2D : public Renderer
{
public:
	Renderer2D();

protected:
	void loadShader();
	void updateContextSize() override;
};

#endif /* GRAPHICS_ENGINE_RENDERER_2D_HPP */
