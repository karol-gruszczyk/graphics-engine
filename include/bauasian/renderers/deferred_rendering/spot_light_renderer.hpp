#ifndef GRAPHICS_ENGINE_SPOT_LIGHT_RENDERER_HPP
#define GRAPHICS_ENGINE_SPOT_LIGHT_RENDERER_HPP

#include "bauasian/mixins/shader_mixin.hpp"
#include "bauasian/scenes/scene_3d.hpp"
#include "bauasian/primitives/cone_volume.hpp"


namespace bauasian
{
	class SpotLightRenderer;
}

class bauasian::SpotLightRenderer : public ShaderMixin
{
public:
	SpotLightRenderer(const glm::uvec2& size);

	void setSize(const glm::uvec2& size);
	void render(const Scene3D* const scene) const;

private:
	std::unique_ptr<ConeVolume> m_light_volume;

	GLint m_location_spot_light_projection_view_matrix;
	GLint m_location_spot_light_screen_size;

};

#endif //GRAPHICS_ENGINE_SPOT_LIGHT_RENDERER_HPP
