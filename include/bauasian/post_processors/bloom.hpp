#ifndef BAUASIAN_BLOOM_HPP
#define BAUASIAN_BLOOM_HPP

#include "bauasian/mixins/shader_mixin.hpp"
#include "bauasian/renderers/frame_buffer.hpp"
#include "bauasian/materials/texture.hpp"
#include "bauasian/shaders/shader_program.hpp"


namespace bauasian
{
	class Bloom;
}

class bauasian::Bloom : public ShaderMixin
{
public:
	Bloom(const glm::uvec2& size);

private:
	std::unique_ptr<FrameBuffer> m_frame_buffer;
	std::shared_ptr<Texture> m_intensity_texture;

};

#endif /* BAUASIAN_BLOOM_HPP */
