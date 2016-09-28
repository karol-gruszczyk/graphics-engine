#ifndef GRAPHICS_ENGINE_FONT_LOADER_HPP
#define GRAPHICS_ENGINE_FONT_LOADER_HPP

#include <ft2build.h>
#include FT_FREETYPE_H
#include <boost/filesystem.hpp>
#include "glyph.hpp"


namespace engine
{
	class FontLoader;
}

class engine::FontLoader final
{
public:
	FontLoader(const boost::filesystem::path& path);
	~FontLoader();

	static const std::string getFreeTypeVersion();

	const std::map<char, Glyph*>& getGlyphs() const;
	const int& getLineSpacing() const;

private:
	FontLoader();
	bool m_is_global = false;
	std::map<char, Glyph*> m_glyphs;
	int m_line_spacing;

	static FT_Library s_ft_lib;
	FontLoader& getGlobalInstance();
};

#endif /* GRAPHICS_ENGINE_FONT_LOADER_HPP */
