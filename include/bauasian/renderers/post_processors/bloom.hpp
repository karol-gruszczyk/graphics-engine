#ifndef BAUASIAN_BLOOM_HPP
#define BAUASIAN_BLOOM_HPP

#include "bauasian/renderers/frame_buffer.hpp"
#include "bauasian/materials/texture.hpp"
#include "bauasian/shaders/shader_program.hpp"


namespace bauasian
{
	class Bloom;
}

class bauasian::Bloom
{
public:
	Bloom(const glm::uvec2& size);
	~Bloom();

private:
	FrameBuffer* m_frame_buffer = nullptr;
	Texture* m_intensity_texture = nullptr;
	ShaderProgram* m_shader;

};

#endif /* BAUASIAN_BLOOM_HPP */
