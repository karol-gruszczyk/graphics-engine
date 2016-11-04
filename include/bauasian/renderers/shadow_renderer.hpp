#ifndef BAUASIAN_SHADOW_RENDERER_HPP
#define BAUASIAN_SHADOW_RENDERER_HPP

#include "bauasian/mixins/shader_mixin.hpp"
#include "bauasian/frame_buffers/frame_buffer.hpp"
#include "bauasian/textures/texture.hpp"
#include "bauasian/scenes/scene_3d.hpp"
#include "bauasian/cameras/orthographic_camera.hpp"
#include "bauasian/cameras/perspective_camera.hpp"
#include "bauasian/uniform_buffers/shadow_buffer.hpp"

#include <glm/glm.hpp>


namespace bauasian
{
	class ShadowRenderer;
}

class bauasian::ShadowRenderer : public SizeMixin, public ShaderMixin
{
public:
	ShadowRenderer(const glm::uvec2& size);

	void setSize(const glm::uvec2& size);
	void render(const Scene3D* const scene, const glm::vec3& light_direction);
	void bind() const;

private:
	std::unique_ptr<FrameBuffer> m_frame_buffer;
	std::shared_ptr<Texture> m_depth_texture;
	ShadowBuffer m_buffer;

	void calculateCameraBounds(const glm::vec3& light_dir);

};

#endif /* BAUASIAN_SHADOW_RENDERER_HPP */
