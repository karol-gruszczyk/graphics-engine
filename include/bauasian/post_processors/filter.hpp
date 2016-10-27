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

class bauasian::Filter
{
public:
	Filter(const boost::filesystem::path& fragment_shader_path, const GLenum& storage = GL_RGBA);
	Filter(Shader& fragment_shader, const GLenum& storage = GL_RGBA);
	virtual ~Filter();

	virtual void setSize(const glm::uvec2& size);
	virtual void process(const Texture* const texture, bool to_screen = true) const;
	const Texture* const getTexture() const;

protected:
	FrameBuffer* m_frame_buffer = nullptr;
	std::shared_ptr<Texture> m_color_texture;
	ShaderProgram* m_shader = nullptr;
	glm::uvec2 m_size;

	void loadShader(Shader& fragment_shader);

private:
	ScreenQuad* m_screen_quad = nullptr;

	void initFrameBuffer(const GLenum& storage);

};

#endif /* BAUASIAN_FILTER_HPP */
