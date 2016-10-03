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
	FontLoader(const boost::filesystem::path& path, unsigned font_size);
	~FontLoader();

	static const std::string getFreeTypeVersion();

	const std::map<char, Glyph*>& getGlyphs() const;
	const int& getLineSpacing() const;
	Texture* getGlyphAtlas() const;

private:
	struct GlyphBitmap
	{
		glm::uvec2 size;
		glm::ivec2 bearing, advance;
		GLubyte* pixels;

		~GlyphBitmap()
		{
			delete[] pixels;
		}
	};

	FontLoader();
	bool m_is_global = false;
	std::map<char, Glyph*> m_glyphs;
	int m_line_spacing;
	Texture* m_glyph_atlas = nullptr;

	static FT_Library s_ft_lib;
	static const unsigned s_first_char = 32;
	static const unsigned s_last_char = 128;

	FontLoader& getGlobalInstance();
	void createGlyphAtlas(const unsigned& glyph_width, const unsigned& glyph_height,
	                      const GlyphBitmap* const glyph_bitmaps);

	static inline unsigned nextPowerOf2(unsigned x);
};

#endif /* GRAPHICS_ENGINE_FONT_LOADER_HPP */
