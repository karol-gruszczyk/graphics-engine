#ifndef BAUASIAN_FXAA_HPP
#define BAUASIAN_FXAA_HPP

#include "post_processor.hpp"
#include "bauasian/shaders/shader_program.hpp"
#include "bauasian/frame_buffers/frame_buffer.hpp"
#include "bauasian/primitives/screen_quad.hpp"


namespace bauasian
{
	class FXAA;
}

class bauasian::FXAA : public PostProcessor
{
public:
	enum Quality
	{
		VERY_LOW = 10, LOW = 12, MEDIUM = 15, HIGH = 20, VERY_HIGH = 25, ULTRA = 29, EXTREME = 39
	};

	FXAA(const glm::uvec2& size, Quality quality = LOW);

	virtual void setSize(const glm::uvec2& size) override;
	virtual void process(unsigned short out_binding = POST_PROCESSING_COLOR_TEXTURE) const override;
	virtual void processToScreen() const override;
	virtual void process(const Texture* texture) const override;
	virtual const Texture* getTexture() const override;

	void setSubPixelRemoval(float sub_pixel_removal) const;
	void setEdgeThreshold(float edge_threshold) const;
	void setEdgeThresholdMin(float edge_threshold_min) const;

private:
	std::unique_ptr<FrameBuffer> m_frame_buffer;
	std::shared_ptr<Texture> m_color_texture;
	std::unique_ptr<ShaderProgram> m_shader;
	std::unique_ptr<ScreenQuad> m_screen_quad;

	GLint m_location_pixel_size;
	GLint m_location_subpix;
	GLint m_location_edge_threshold;
	GLint m_location_edge_threshold_min;

};

#endif /* BAUASIAN_FXAA_HPP */
