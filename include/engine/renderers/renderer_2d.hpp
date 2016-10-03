#ifndef GRAPHICS_ENGINE_RENDERER_2D_HPP
#define GRAPHICS_ENGINE_RENDERER_2D_HPP

#include "renderer.hpp"
#include "engine/context_width_interface.hpp"


namespace engine
{
	class Renderer2D;
}

class engine::Renderer2D : public Renderer
{
public:
	Renderer2D();

protected:
	void loadShader();
	void updateContextSize() override;
};

#endif /* GRAPHICS_ENGINE_RENDERER_2D_HPP */
