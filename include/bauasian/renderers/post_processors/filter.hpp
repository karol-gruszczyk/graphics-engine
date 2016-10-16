#ifndef BAUASIAN_FILTER_HPP
#define BAUASIAN_FILTER_HPP

#include "bauasian/renderers/frame_buffer.hpp"
#include "bauasian/materials/texture.hpp"
#include "bauasian/primitives/screen_quad.hpp"
#include "bauasian/shaders/shader_program.hpp"

#include <GL/glew.h>


namespace bauasian
{
	class Filter;
}

class bauasian::Filter : public FrameBuffer
{
public:
	Filter(const boost::filesystem::path& fragment_shader_path);
	Filter(Shader& fragment_shader);
	virtual ~Filter();

	virtual void setContextSize(const unsigned& width, const unsigned& height) const;
	void renderToScreen() const;

protected:
	ShaderProgram* m_shader = nullptr;

	void loadShader(Shader& fragment_shader);

private:
	GLuint m_rbo_id;
	Texture* m_color_texture = nullptr;
	ScreenQuad* m_screen_quad = nullptr;

	void initFrameBuffer();

};

#endif /* BAUASIAN_FILTER_HPP */
