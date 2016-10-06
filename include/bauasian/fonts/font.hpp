#ifndef BAUASIAN_FONT_HPP
#define BAUASIAN_FONT_HPP

#include "glyph.hpp"
#include "bauasian/context_size_interface.hpp"
#include "bauasian/shaders/shader_program.hpp"

#include <map>

#include <boost/filesystem.hpp>


namespace bauasian
{
	class Font;
}

class bauasian::Font : public bauasian::ContextSizeInterface
{
	friend class Text;

public:
	static Font* loadFromFile(const boost::filesystem::path& path, unsigned font_size = 48);
	float getScale(const unsigned& font_size) const;

	void bind() const;
	void unbind() const;

private:
	Font();
	~Font();

	static std::map<std::tuple<std::string, unsigned>, Font*> s_fonts;
	static ShaderProgram* s_shader;

	bool m_is_static_instance = false;
	unsigned m_font_size;
	std::map<char, Glyph*> m_glyphs;
	GLint m_line_spacing;
	Texture* m_glyph_atlas = nullptr;

	static Font& getStaticInstance();

	void loadShader();
	void unloadShader();
	void updateContextSize() override;
};

#endif /* BAUASIAN_FONT_HPP */
