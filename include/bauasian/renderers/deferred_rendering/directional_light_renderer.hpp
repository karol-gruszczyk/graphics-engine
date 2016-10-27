#ifndef BAUASIAN_DIRECTIONAL_LIGHT_RENDERER_HPP
#define BAUASIAN_DIRECTIONAL_LIGHT_RENDERER_HPP

#include "bauasian/shaders/shader.hpp"
#include "bauasian/primitives/screen_quad.hpp"
#include "bauasian/scenes/scene_3d.hpp"


namespace bauasian
{
	class DirectionalLightRenderer;
}

class bauasian::DirectionalLightRenderer
{
public:
	DirectionalLightRenderer();
	~DirectionalLightRenderer();

	void render(const Scene3D* const scene) const;

private:
	ShaderProgram* m_shader;
	ScreenQuad* m_light_volume;

};


#endif /* BAUASIAN_DIRECTIONAL_LIGHT_RENDERER_HPP */
