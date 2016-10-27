#include "font_factory.hpp"
#include "font_loader.hpp"


using bauasian::FontFactory;
using bauasian::Font;

FontFactory& bauasian::FontFactory::getInstance()
{
	static FontFactory instance;
	return instance;
}

Font* FontFactory::getFont(const boost::filesystem::path& path, unsigned font_size /* = 48 */)
{
	if (!boost::filesystem::exists(path))
		throw FileNotFoundException(path);

	auto key = std::make_tuple(boost::filesystem::canonical(path).string(), font_size);
	if (m_fonts.count(key))
		return m_fonts[key];

	FontLoader loader(path, font_size);
	Font* font = new Font(font_size, loader.getGlyphs(), loader.getGlyphAtlas(), loader.getLineSpacing());
	m_fonts[key] = font;
	return font;
}

FontFactory::FontFactory()
{
	Font::loadShader();
}

FontFactory::~FontFactory()
{
	for (const auto& font : m_fonts)
		delete font.second;
}
