#include "font_loader.hpp"
#include "engine/engine.hpp"


using engine::FontLoader;
using engine::Glyph;
using engine::Texture;

FT_Library FontLoader::s_ft_lib;

FontLoader::FontLoader(const boost::filesystem::path& path)
{
	getGlobalInstance();

	auto full_path = boost::filesystem::canonical(path).string();
	Engine::getInstance().logInfo("Loading font '" + full_path + "'");

	FT_Face face;
	if (FT_New_Face(s_ft_lib, path.string().c_str(), 0, &face) != 0)
	{
		Engine::getInstance().logError("FreeType failed to load font '" + full_path + "'");
		return;
	}

	FT_Set_Pixel_Sizes(face, 0, 48);
	m_line_spacing = (int)face->size->metrics.height >> 6;
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);  // disable byte-alignment restriction, for dev purposes only
	for (GLubyte ch = 0; ch < 128; ch++)
	{
		if (FT_Load_Char(face, ch, FT_LOAD_RENDER) != 0)
		{
			Engine::getInstance().logError("FreeType failed loading glyph '" + std::to_string(ch) + "' for font '"
			                               + full_path + "'");
			return;
		}
		const auto& glyph = face->glyph;
		auto texture = new Texture(glyph->bitmap.width, glyph->bitmap.rows, glyph->bitmap.buffer, GL_RED, GL_RED,
		                           false);
		m_glyphs[ch] = new Glyph(texture,
		                         { glyph->bitmap.width, glyph->bitmap.rows },
		                         { glyph->bitmap_left, glyph->bitmap_top },
		                         (GLint) glyph->advance.x >> 6);
	}
	FT_Done_Face(face);

	Engine::getInstance().logInfo("Font '" + full_path + "' loaded");
}

FontLoader::~FontLoader()
{
	if (m_is_global)
	{
		FT_Done_FreeType(s_ft_lib);
		Engine::getInstance().logInfo("FreeType unloaded");
	}
}

const std::string FontLoader::getFreeTypeVersion()
{
	FT_Int major, minor, patch;
	FT_Library_Version(s_ft_lib, &major, &minor, &patch);
	return std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(patch);
}

const std::map<char, Glyph*>& FontLoader::getGlyphs() const
{
	return m_glyphs;
}

const int& FontLoader::getLineSpacing() const
{
	return m_line_spacing;
}

FontLoader::FontLoader()
		: m_is_global(true)
{
	if (FT_Init_FreeType(&s_ft_lib) != 0)
		Engine::getInstance().logError("FreeType failed to initialize");
	else
		Engine::getInstance().logInfo("FreeType " + getFreeTypeVersion() + " loaded");
}

FontLoader& FontLoader::getGlobalInstance()
{
	static FontLoader instance;
	return instance;
}
