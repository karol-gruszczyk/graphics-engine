#ifndef BAUASIAN_GEOMETRY_RENDERER_HPP
#define BAUASIAN_GEOMETRY_RENDERER_HPP

#include "bauasian/mixins/shader_mixin.hpp"
#include "bauasian/renderers/frame_buffer.hpp"
#include "bauasian/shaders/shader_program.hpp"
#include "bauasian/textures/texture.hpp"
#include "bauasian/scenes/scene_3d.hpp"


namespace bauasian
{
	class GeometryRenderer;
}

class bauasian::GeometryRenderer : public ShaderMixin
{
public:
	GeometryRenderer(const glm::uvec2& size, const std::shared_ptr<FrameBufferAttachment>& depth_buffer);

	void setSize(const glm::uvec2& size);
	void render(const Scene3D* const scene) const;

private:
	std::unique_ptr<FrameBuffer> m_frame_buffer;

	std::shared_ptr<Texture> m_albedo_buffer;
	std::shared_ptr<Texture> m_specular_buffer;
	std::shared_ptr<Texture> m_normal_buffer;
	std::shared_ptr<Texture> m_position_buffer;

};

#endif /* BAUASIAN_GEOMETRY_RENDERER_HPP */
