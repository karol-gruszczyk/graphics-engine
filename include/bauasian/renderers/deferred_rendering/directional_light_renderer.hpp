#ifndef BAUASIAN_DIRECTIONAL_LIGHT_RENDERER_HPP
#define BAUASIAN_DIRECTIONAL_LIGHT_RENDERER_HPP

#include "bauasian/mixins/shader_mixin.hpp"
#include "bauasian/primitives/screen_quad.hpp"
#include "bauasian/scenes/scene_3d.hpp"


namespace bauasian
{
	class DirectionalLightRenderer;
}

class bauasian::DirectionalLightRenderer : public ShaderMixin
{
public:
	DirectionalLightRenderer();

	void render(const Scene3D* const scene) const;

private:
	ScreenQuad m_light_volume;

};

#endif /* BAUASIAN_DIRECTIONAL_LIGHT_RENDERER_HPP */
