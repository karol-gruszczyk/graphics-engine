#ifndef BAUASIAN_POINT_LIGHT_RENDERER_HPP
#define BAUASIAN_POINT_LIGHT_RENDERER_HPP

#include "bauasian/mixins/shader_mixin.hpp"
#include "bauasian/primitives/sphere_volume.hpp"
#include "bauasian/scenes/scene_3d.hpp"


namespace bauasian
{
	class PointLightRenderer;
}

class bauasian::PointLightRenderer : public ShaderMixin
{
public:
	PointLightRenderer(const glm::uvec2& size);

	void setSize(const glm::uvec2& size);
	void render(const Scene3D* const scene) const;

private:
	SphereVolume m_light_volume;

	GLint m_location_point_light_screen_size;

};

#endif /* BAUASIAN_POINT_LIGHT_RENDERER_HPP */
