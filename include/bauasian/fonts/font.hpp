#ifndef BAUASIAN_FONT_HPP
#define BAUASIAN_FONT_HPP

#include "glyph.hpp"
#include "bauasian/context_size_observer.hpp"
#include "bauasian/shaders/shader_program.hpp"

#include <map>

#include <boost/filesystem.hpp>


namespace bauasian
{
	class Font;
}

class bauasian::Font : public bauasian::ContextSizeObserver
{
	friend class Text;

public:
	Font(const unsigned& font_size, const std::map<char, Glyph*>& glyphs, Texture* glyph_atlas,
	     const int& line_spacing);
	virtual ~Font();

	static void loadShader();
	static void unloadShader();

	float getScale(const unsigned& font_size) const;
	void bind() const;
	void unbind() const;

private:
	static ShaderProgram* s_shader;
	static GLint m_location_projection_matrix;

	unsigned m_font_size;
	std::map<char, Glyph*> m_glyphs;
	Texture* m_glyph_atlas = nullptr;
	GLint m_line_spacing;

	void updateContextSize() override;
};

#endif /* BAUASIAN_FONT_HPP */
