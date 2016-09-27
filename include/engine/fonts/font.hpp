#ifndef GRAPHICS_ENGINE_FONT_HPP
#define GRAPHICS_ENGINE_FONT_HPP

#include <boost/filesystem.hpp>
#include <map>
#include "engine/materials/texture.hpp"


namespace engine
{
	class Font;
}

class engine::Font
{
public:
	~Font();
	static Font *loadFromFile(const boost::filesystem::path &path);

private:
	Font();

	static std::map<std::string, Font *> s_fonts;

	bool m_is_static_instance = false;
	std::map<wchar_t, Texture*> m_char_bitmaps;

	static Font &getStaticInstance();
};

#endif /* GRAPHICS_ENGINE_FONT_HPP */
