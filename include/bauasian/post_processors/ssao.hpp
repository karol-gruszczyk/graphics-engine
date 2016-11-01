#ifndef BAUASIAN_SSAO_HPP
#define BAUASIAN_SSAO_HPP

#include "filter.hpp"
#include "ssao_blur.hpp"


namespace bauasian
{
	class SSAO;
}

class bauasian::SSAO : public Filter
{
public:
	SSAO(const glm::uvec2& size);

	void setSize(const glm::uvec2& size) override;
	void process(const unsigned short& out_binding = POST_PROCESSING_COLOR_TEXTURE) const override;
	void setKernelSize(const int& kernel_size) const;
	void setRadius(const float& radius) const;
	void setPower(const float& power) const;

private:
	SSAOBlur m_ssao_blur;
	std::unique_ptr<Texture> m_noise_texture;

	GLint m_location_kernel_size;
	GLint m_location_ssao_radius;
	GLint m_location_ssao_power;
	GLint m_location_noise_scale;

	void generateKernel();
	void generateNoiseTexture();

};

#endif /* BAUASIAN_SSAO_HPP */
