#ifndef BAUASIAN_DEFERRED_RENDERER_HPP
#define BAUASIAN_DEFERRED_RENDERER_HPP

#include "frame_buffer.hpp"
#include "post_processors/filter.hpp"
#include "bauasian/materials/texture.hpp"
#include "bauasian/scenes/scene_3d.hpp"
#include "bauasian/interfaces/size_interface.hpp"
#include "bauasian/primitives/screen_quad.hpp"


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

	GLint m_location_dir_light_direction;
	GLint m_location_dir_light_diffuse_color;
	GLint m_location_dir_light_specular_color;

	GLint m_location_point_light_position;
	GLint m_location_point_light_diffuse_color;
	GLint m_location_point_light_specular_color;
	GLint m_location_point_light_attenuation;

	GLint m_location_spot_light_position;
	GLint m_location_spot_light_direction;
	GLint m_location_spot_light_diffuse_color;
	GLint m_location_spot_light_specular_color;
	GLint m_location_spot_light_attenuation;
	GLint m_location_spot_light_inner_angle;
	GLint m_location_spot_light_outer_angle;

	void initDirectionalLightShader();
	void initPointLightShader();
	void initSpotLightShader();
	void initLightShaderUniformLocation(ShaderProgram* shader) const;
	void renderGeometry(Scene3D* scene) const;
	void renderLighting(Scene3D* scene) const;
	void renderDirectionalLights(Scene3D* scene) const;
	void renderPointLights(Scene3D* scene) const;
	void renderSpotLights(Scene3D* scene) const;

};

#endif /* BAUASIAN_DEFERRED_RENDERER_HPP */
