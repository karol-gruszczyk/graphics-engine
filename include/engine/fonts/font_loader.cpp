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
	m_line_spacing = (int) face->size->metrics.height >> 6;
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);  // disable byte-alignment restriction, for dev purposes only

	GlyphBitmap* glyph_bitmaps = new GlyphBitmap[s_last_char - s_first_char];
	unsigned max_glyph_width(0), max_glyph_height(0);
	for (GLubyte ch = s_first_char; ch < s_last_char; ch++)
	{
		if (FT_Load_Char(face, ch, FT_LOAD_RENDER) != 0)
		{
			Engine::getInstance().logError("FreeType failed loading glyph '" + std::to_string(ch) + "' for font '"
			                               + full_path + "'");
			return;
		}
		const auto& glyph = face->glyph;

		auto& glyph_bitmap = glyph_bitmaps[ch - s_first_char];
		glyph_bitmap.width = glyph->bitmap.width;
		glyph_bitmap.height = glyph->bitmap.rows;
		glyph_bitmap.pixels = new GLubyte[glyph->bitmap.width * glyph->bitmap.rows];
		memcpy(glyph_bitmap.pixels, glyph->bitmap.buffer,
		       glyph->bitmap.width * glyph->bitmap.rows * sizeof(GLubyte));  // change to c++14


		max_glyph_width = std::max(max_glyph_width, glyph_bitmap.width);
		max_glyph_height = std::max(max_glyph_height, glyph_bitmap.height);

		auto texture = new Texture(glyph->bitmap.width, glyph->bitmap.rows, glyph->bitmap.buffer, GL_RED, GL_RED,
		                           false);
		m_glyphs[ch] = new Glyph(texture,
		                         { glyph->bitmap.width, glyph->bitmap.rows },
		                         { glyph->bitmap_left, glyph->bitmap_top },
		                         { (GLint) glyph->advance.x >> 6, (GLint) glyph->advance.y >> 6 });

	}
	FT_Done_Face(face);

	createGlyphAtlas(max_glyph_width, max_glyph_height, glyph_bitmaps);

	delete[] glyph_bitmaps;

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

Texture* FontLoader::getGlyphAtlas() const
{
	return m_glyph_atlas;
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

void FontLoader::createGlyphAtlas(const unsigned& glyph_width, const unsigned& glyph_height,
                                  const GlyphBitmap* const glyph_bitmaps)
{
	unsigned num_glyphs = s_last_char - s_first_char;
	unsigned atlas_glyphs_dimension = (unsigned)ceil(sqrt(num_glyphs));
	unsigned atlas_width = nextPowerOf2(atlas_glyphs_dimension * glyph_width);
	unsigned atlas_height = nextPowerOf2(atlas_glyphs_dimension * glyph_height);
	GLubyte* atlas_pixels = new GLubyte[atlas_width * atlas_height];
	memset(atlas_pixels, 0, atlas_width * atlas_height * sizeof(GLubyte));
	unsigned current_row(0), current_column(0);
	for (auto i = 0; i < num_glyphs; i++)
	{
		const auto& glyph = glyph_bitmaps[i];
		for (auto h = 0; h < glyph.height; h++)
		{
			for (auto w = 0; w < glyph.width; w++)
			{
				auto offset = current_row * glyph_height * atlas_width
				              + current_column * glyph_width;
				atlas_pixels[offset + h * atlas_width + w] = glyph.pixels[h * glyph.width + w];
			}
		}
		if (++current_column >= atlas_glyphs_dimension)
		{
			current_column = 0;
			current_row++;
		}
	}

	// inverting all pixels vertically
	for (auto i = 0; i < atlas_height / 2; i++)
	{
		for (auto j = 0; j < atlas_width; j++)
		{
			const auto temp = atlas_pixels[i * atlas_width + j];
			atlas_pixels[i * atlas_width + j] = atlas_pixels[(atlas_height - i - 1) * atlas_width + j];
			atlas_pixels[(atlas_height - i - 1) * atlas_width + j] = temp;
		}
	}
	m_glyph_atlas = new Texture(atlas_width, atlas_height, atlas_pixels, GL_RED, GL_RED, false);
	m_glyph_atlas->save("atlas.png");  // only for dev
}

inline unsigned FontLoader::nextPowerOf2(unsigned x)
{
	unsigned num(1);
	while ((num = num << 1) < x);
	return num;
}
