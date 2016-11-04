#ifndef BAUASIAN_SPOT_LIGHT_RENDERER_HPP
#define BAUASIAN_SPOT_LIGHT_RENDERER_HPP

#include "bauasian/mixins/shader_mixin.hpp"
#include "bauasian/scenes/scene_3d.hpp"
#include "bauasian/primitives/cone_volume.hpp"


namespace bauasian
{
	class SpotLightPass;
}

class bauasian::SpotLightPass : public ShaderMixin
{
public:
	SpotLightPass(const glm::uvec2& size);

	void setSize(const glm::uvec2& size);
	void render(const Scene3D* scene) const;

private:
	ConeVolume m_light_volume;

	GLint m_location_spot_light_screen_size;

};

#endif /* BAUASIAN_SPOT_LIGHT_RENDERER_HPP */
