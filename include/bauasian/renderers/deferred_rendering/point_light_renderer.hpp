#ifndef BAUASIAN_POINT_LIGHT_RENDERER_HPP
#define BAUASIAN_POINT_LIGHT_RENDERER_HPP

#include "bauasian/primitives/sphere_volume.hpp"
#include "bauasian/scenes/scene_3d.hpp"


namespace bauasian
{
	class PointLightRenderer;
}

class bauasian::PointLightRenderer
{
public:
	PointLightRenderer(const glm::uvec2& size);
	~PointLightRenderer();

	void setSize(const glm::uvec2& size);
	void render(const Scene3D* const scene) const;
	const ShaderProgram* const getShader() const;

private:
	ShaderProgram* m_shader;
	SphereVolume* m_light_volume;

	GLint m_location_point_light_projection_view_matrix;
	GLint m_location_point_light_screen_size;

};

#endif /* BAUASIAN_POINT_LIGHT_RENDERER_HPP */
