#ifndef GRAPHICS_ENGINE_FONT_HPP
#define GRAPHICS_ENGINE_FONT_HPP

#include <boost/filesystem.hpp>
#include <map>
#include "glyph.hpp"
#include "engine/shaders/shader_program.hpp"


namespace engine
{
	class Font;
}

class engine::Font
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
};

#endif /* GRAPHICS_ENGINE_FONT_HPP */
