#ifndef BAUASIAN_RENDERER_2D_HPP
#define BAUASIAN_RENDERER_2D_HPP

#include "bauasian/mixins/shader_mixin.hpp"
#include "bauasian/scenes/scene_2d.hpp"
#include "bauasian/context_size_observer.hpp"


namespace bauasian
{
	class Renderer2D;
}

class bauasian::Renderer2D : public ContextSizeObserver, public ShaderMixin
{
public:
	Renderer2D();
	virtual ~Renderer2D() {}

	void clearScreen()const;
	void render(const Scene2D* scene) const;

protected:
	glm::mat4 m_projection_matrix;

	GLint m_location_projection_matrix;
	GLint m_location_model_matrix;

	void updateContextSize() override;

};

#endif /* BAUASIAN_RENDERER_2D_HPP */
