#ifndef BAUASIAN_RENDERER_2D_HPP
#define BAUASIAN_RENDERER_2D_HPP

#include "renderer.hpp"
#include "scene_2d.hpp"
#include "bauasian/context_width_interface.hpp"


namespace bauasian
{
	class Renderer2D;
}

class bauasian::Renderer2D : public Renderer
{
public:
	Renderer2D();

	void render(const Scene2D* scene) const;

protected:
	void loadShader();
	void updateContextSize() override;
};

#endif /* BAUASIAN_RENDERER_2D_HPP */
