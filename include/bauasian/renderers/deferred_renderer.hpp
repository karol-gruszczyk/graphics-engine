#ifndef BAUASIAN_DEFERRED_RENDERER_HPP
#define BAUASIAN_DEFERRED_RENDERER_HPP

#include "frame_buffer.hpp"
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
	~DeferredRenderer();

	virtual void setSize(const glm::uvec2& size) override;

	void clearScreen() const;
	void render(Scene3D* scene) const;

private:
	FrameBuffer* m_frame_buffer;
	Texture* m_albedo_buffer;
	Texture* m_specular_buffer;
	Texture* m_normal_buffer;
	Texture* m_position_buffer;
	ShaderProgram* m_geometry_shader;
	ShaderProgram* m_dir_light_shader;
	ScreenQuad* m_screen_quad;

	GLint m_location_dir_light_direction;
	GLint m_location_dir_light_diffuse_color;
	GLint m_location_dir_light_specular_color;

	void initUniformLocations(ShaderProgram* shader) const;

};

#endif /* BAUASIAN_DEFERRED_RENDERER_HPP */