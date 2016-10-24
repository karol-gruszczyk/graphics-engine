#ifndef BAUASIAN_DEFERRED_RENDERER_HPP
#define BAUASIAN_DEFERRED_RENDERER_HPP

#include "frame_buffer.hpp"
#include "post_processors/filter.hpp"
#include "bauasian/materials/texture.hpp"
#include "bauasian/scenes/scene_3d.hpp"
#include "bauasian/interfaces/size_interface.hpp"
#include "bauasian/primitives/screen_quad.hpp"
#include "bauasian/primitives/sphere_volume.hpp"


namespace bauasian
{
	class DeferredRenderer;
}

class bauasian::DeferredRenderer : public SizeInterface
{
public:
	DeferredRenderer(const glm::uvec2 size);
	virtual ~DeferredRenderer();

	virtual void setSize(const glm::uvec2& size) override;

	void addFilter(Filter* filter);
	void clearScreen() const;
	void render(Scene3D* scene) const;

private:
	std::list<Filter*> m_filters;

	FrameBuffer* m_frame_buffer;
	Texture* m_albedo_buffer;
	Texture* m_specular_buffer;
	Texture* m_normal_buffer;
	Texture* m_position_buffer;
	ShaderProgram* m_geometry_shader;
	ShaderProgram* m_dir_light_shader;
	ShaderProgram* m_point_light_shader;
	ShaderProgram* m_spot_light_shader;
	ScreenQuad* m_screen_quad;
	SphereVolume* m_sphere_volume;

	GLint m_location_point_light_projection_view_matrix;
	GLint m_location_point_light_screen_size;

	GLint m_location_spot_light_screen_size;

	void initDirectionalLightShader();
	void initPointLightShader();
	void initSpotLightShader();
	void initLightShaderUniformLocation(ShaderProgram* shader) const;
	void geometryPass(Scene3D* scene) const;
	void renderLighting(Scene3D* scene) const;
	void directionalLightPass(Scene3D* scene) const;
	void pointLightPass(Scene3D* scene) const;
	void spotLightPass(Scene3D* scene) const;

};

#endif /* BAUASIAN_DEFERRED_RENDERER_HPP */
