#ifndef GRAPHICS_ENGINE_FONT_LOADER_HPP
#define GRAPHICS_ENGINE_FONT_LOADER_HPP

#include <ft2build.h>
#include FT_FREETYPE_H
#include <boost/filesystem.hpp>


namespace engine
{
	class FontLoader;
}

class engine::FontLoader final
{
public:
	FontLoader(const boost::filesystem::path &path);
	~FontLoader();

	const std::string getFreeTypeVersion();
private:
	FontLoader();
	bool m_is_global = false;
	FT_Face m_face;

	static FT_Library *s_ft_lib;
	FontLoader &getGlobalInstance();
};

#endif /* GRAPHICS_ENGINE_FONT_LOADER_HPP */
