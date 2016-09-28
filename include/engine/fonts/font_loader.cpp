#include "font_loader.hpp"
#include "engine/config.hpp"


using engine::FontLoader;
using engine::Texture;

FT_Library FontLoader::s_ft_lib;

FontLoader::FontLoader(const boost::filesystem::path& path)
{
	getGlobalInstance();

	auto full_path = boost::filesystem::canonical(path).string();
	Config::getInstance().logInfo("Loading font '" + full_path + "'");

	if (FT_New_Face(s_ft_lib, path.string().c_str(), 0, &m_face) != 0)
	{
		Config::getInstance().logError("FreeType failed to load font '" + full_path + "'");
		return;
	}

	FT_Set_Pixel_Sizes(m_face, 0, 48);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);  // disable byte-alignment restriction
	for (GLubyte ch = 0; ch < 128; ch++)
	{
		if (FT_Load_Char(m_face, ch, FT_LOAD_RENDER) != 0)
		{
			Config::getInstance().logError("FreeType failed loading glyph '" + std::to_string(ch) + "' for font '"
			                               + full_path + "'");
			return;
		}
		FT_GlyphSlot glyph = m_face->glyph;
		FT_Bitmap bitmap = glyph->bitmap;
		m_glyphs[ch] = new Texture(bitmap.width, bitmap.rows, bitmap.buffer, GL_RED, GL_RED, false);
	}
	FT_Done_Face(m_face);

	Config::getInstance().logInfo("Font '" + full_path + "' loaded");
}

FontLoader::~FontLoader()
{
	if (m_is_global)
	{
		FT_Done_FreeType(s_ft_lib);
		Config::getInstance().logInfo("FreeType unloaded");
	}
}

const std::string FontLoader::getFreeTypeVersion()
{
	FT_Int major, minor, patch;
	FT_Library_Version(s_ft_lib, &major, &minor, &patch);
	return std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(patch);
}

std::map<char, Texture*> FontLoader::getGlyphs()
{
	return m_glyphs;
}

FontLoader::FontLoader()
		: m_is_global(true)
{
	if (FT_Init_FreeType(&s_ft_lib) != 0)
		Config::getInstance().logError("FreeType failed to initialize");
	else
		Config::getInstance().logInfo("FreeType " + getFreeTypeVersion() + " loaded");
}

FontLoader& FontLoader::getGlobalInstance()
{
	static FontLoader instance;
	return instance;
}
