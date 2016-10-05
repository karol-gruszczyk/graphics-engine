#ifndef BAUASIAN_FONT_HPP
#define BAUASIAN_FONT_HPP

#include <boost/filesystem.hpp>
#include <map>
#include "glyph.hpp"
#include "bauasian/shaders/shader_program.hpp"
#include "bauasian/context_size_interface.hpp"


namespace bauasian
{
	class Font;
}

class bauasian::Font : public bauasian::ContextSizeInterface
{
	friend class Text;
public:
	~Font();
	static Font* loadFromFile(const boost::filesystem::path& path, unsigned font_size);
	void bind() const;

private:
	Font();

	static std::map<std::string, Font*> s_fonts;
	static ShaderProgram* s_shader;

	bool m_is_static_instance = false;
	std::map<char, Glyph*> m_glyphs;
	GLint m_line_spacing;
	Texture* m_glyph_atlas = nullptr;

	static Font& getStaticInstance();

	void loadShader();
	void unloadShader();
	void updateContextSize() override;
};

#endif /* BAUASIAN_FONT_HPP */
