#ifndef BAUASIAN_FONT_FACTORY_HPP
#define BAUASIAN_FONT_FACTORY_HPP

#include "font.hpp"


namespace bauasian
{
	class FontFactory;
}

class bauasian::FontFactory
{
public:
	FontFactory(const FontFactory&) = delete;
	FontFactory& operator=(const FontFactory&) = delete;

	static FontFactory& getInstance();

	Font* getFont(const boost::filesystem::path& path, unsigned font_size = 48);

private:
	FontFactory();
	~FontFactory();

	std::map<std::tuple<std::string, unsigned>, Font*> m_fonts;

};

#endif /* BAUASIAN_FONT_FACTORY_HPP */
