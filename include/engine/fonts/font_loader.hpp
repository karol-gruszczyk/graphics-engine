#ifndef GRAPHICS_ENGINE_FONT_LOADER_HPP
#define GRAPHICS_ENGINE_FONT_LOADER_HPP

#include <ft2build.h>
#include FT_FREETYPE_H
#include <boost/filesystem.hpp>
#include "engine/materials/texture.hpp"


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

	std::map<char, Texture*> getGlyphs();

private:
	FontLoader();
	bool m_is_global = false;
	FT_Face m_face;
	std::map<char, Texture*> m_glyphs;

	static FT_Library s_ft_lib;
	FontLoader& getGlobalInstance();
};

#endif /* GRAPHICS_ENGINE_FONT_LOADER_HPP */
