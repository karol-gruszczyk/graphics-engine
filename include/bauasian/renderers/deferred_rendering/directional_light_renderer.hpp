#ifndef BAUASIAN_DIRECTIONAL_LIGHT_RENDERER_HPP
#define BAUASIAN_DIRECTIONAL_LIGHT_RENDERER_HPP

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

	void render(const Scene3D* const scene) const;
	const ShaderProgram* const getShader() const;

private:
	std::unique_ptr<ShaderProgram> m_shader;
	std::unique_ptr<ScreenQuad> m_light_volume;

};

#endif /* BAUASIAN_DIRECTIONAL_LIGHT_RENDERER_HPP */
