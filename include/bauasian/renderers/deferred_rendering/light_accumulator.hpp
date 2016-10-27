#ifndef BAUASIAN_LIGHT_RENDERER_HPP
#define BAUASIAN_LIGHT_RENDERER_HPP

#include "bauasian/renderers/frame_buffer.hpp"
#include "bauasian/materials/texture.hpp"
#include "bauasian/scenes/scene_3d.hpp"


namespace bauasian
{
	class LightAccumulator;
}

class bauasian::LightAccumulator
{
public:
	LightAccumulator(const glm::uvec2& size, const std::shared_ptr<FrameBufferAttachment>& depth_buffer);
	~LightAccumulator();

	void setSize(const glm::uvec2& size);
	void render(const Scene3D* const scene);

private:
	glm::uvec2 m_size;
	FrameBuffer* m_frame_buffer = nullptr;
	std::shared_ptr<Texture> m_accumulation_buffer;

};


#endif /* BAUASIAN_LIGHT_RENDERER_HPP */
