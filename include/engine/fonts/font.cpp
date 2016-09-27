#include "font.hpp"
#include "font_loader.hpp"
#include "engine/exceptions/file_not_found_exception.hpp"


using engine::Font;

std::map<std::string, Font *> Font::s_fonts;

Font *Font::loadFromFile(const boost::filesystem::path &path)
{
	if (!boost::filesystem::exists(path))
		throw FileNotFoundException(path);

	auto full_path = boost::filesystem::canonical(path).string();
	if (s_fonts.count(full_path))
		return s_fonts[full_path];

	FontLoader loader(path);

	return new Font();
}

Font::~Font()
{
	if (m_is_static_instance)
	{
		for (const auto &font : s_fonts)
			delete font.second;
	}
}

Font::Font()
{}

Font &Font::getStaticInstance()
{
	static Font instance;
	return instance;
}
