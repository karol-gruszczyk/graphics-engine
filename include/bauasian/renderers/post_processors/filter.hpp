#ifndef BAUASIAN_FILTER_HPP
#define BAUASIAN_FILTER_HPP


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
	Filter(const boost::filesystem::path& fragment_shader_path);
	virtual ~Filter();

	virtual void setContextSize(const unsigned& width, const unsigned& height) const;
	void bind() const;
	void unbind() const;
	void clear() const;
	void renderToScreen() const;

protected:
	ShaderProgram* m_shader = nullptr;

private:
	GLuint m_fbo_id, m_rbo_id;
	Texture* m_color_texture = nullptr;
	ScreenQuad* m_screen_quad = nullptr;
};

#endif /* BAUASIAN_FILTER_HPP */
