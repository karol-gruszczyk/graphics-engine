#include "font_loader.hpp"
#include "bauasian/bauasian.hpp"

#include <chrono>


using bauasian::FontLoader;
using bauasian::Glyph;
using bauasian::Texture;

FT_Library FontLoader::s_ft_lib;

FontLoader::FontLoader(const boost::filesystem::path& path, unsigned font_size)
{
	getGlobalInstance();

	auto full_path = boost::filesystem::canonical(path).string();
	Bauasian::getInstance().logInfo("Loading font '" + full_path + "'");
	using namespace std::chrono;
	auto loading_start_time = steady_clock::now();

	FT_Face face;
	if (FT_New_Face(s_ft_lib, path.string().c_str(), 0, &face) != 0)
	{
		Bauasian::getInstance().logError("FreeType failed to load font '" + full_path + "'");
		return;
	}

	FT_Set_Pixel_Sizes(face, 0, font_size);
	m_line_spacing = (int) face->size->metrics.height >> 6;

	GlyphBitmap* glyph_bitmaps = new GlyphBitmap[s_last_char - s_first_char];
	unsigned max_glyph_width(0), max_glyph_height(0);
	for (GLubyte ch = s_first_char; ch < s_last_char; ch++)
	{
		if (FT_Load_Char(face, ch, FT_LOAD_RENDER) != 0)
		{
			Bauasian::getInstance().logError("FreeType failed loading glyph '" + std::to_string(ch) + "' for font '"
			                                 + full_path + "'");
			return;
		}
		const auto& glyph = face->glyph;

		auto& glyph_bitmap = glyph_bitmaps[ch - s_first_char];
		glyph_bitmap.size = { glyph->bitmap.width, glyph->bitmap.rows };
		glyph_bitmap.bearing = { glyph->bitmap_left, glyph->bitmap_top };
		glyph_bitmap.advance = { (GLint) glyph->advance.x >> 6, (GLint) glyph->advance.y >> 6 };
		glyph_bitmap.pixels = new GLubyte[glyph->bitmap.width * glyph->bitmap.rows];
		std::memcpy(glyph_bitmap.pixels, glyph->bitmap.buffer,
		            glyph->bitmap.width * glyph->bitmap.rows * sizeof(GLubyte));


		max_glyph_width = std::max(max_glyph_width, glyph_bitmap.size.x);
		max_glyph_height = std::max(max_glyph_height, glyph_bitmap.size.y);
	}
	FT_Done_Face(face);

	createGlyphAtlas(max_glyph_width, max_glyph_height, glyph_bitmaps);

	delete[] glyph_bitmaps;

	duration<double, std::milli> loading_time = steady_clock::now() - loading_start_time;
	Bauasian::getInstance().logInfo(
			"Font '" + full_path + "' loaded in " + std::to_string(loading_time.count()) + " ms");
}

FontLoader::~FontLoader()
{
	if (m_is_global)
	{
		FT_Done_FreeType(s_ft_lib);
		Bauasian::getInstance().logInfo("FreeType unloaded");
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

int FontLoader::getLineSpacing() const
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
		Bauasian::getInstance().logError("FreeType failed to initialize");
	else
		Bauasian::getInstance().logInfo("FreeType " + getFreeTypeVersion() + " loaded");
}

FontLoader& FontLoader::getGlobalInstance()
{
	static FontLoader instance;
	return instance;
}

void FontLoader::createGlyphAtlas(unsigned glyph_width, unsigned glyph_height,
								  const GlyphBitmap* glyph_bitmaps)
{
	unsigned num_glyphs = s_last_char - s_first_char;
	unsigned atlas_glyphs_per_line = (unsigned) ceil(sqrt(num_glyphs));
	unsigned atlas_width = nextPowerOf2(atlas_glyphs_per_line * glyph_width);
	unsigned atlas_height = nextPowerOf2(atlas_glyphs_per_line * glyph_height);
	GLubyte* atlas_pixels = new GLubyte[atlas_width * atlas_height];
	std::memset(atlas_pixels, 0, atlas_width * atlas_height * sizeof(GLubyte));
	unsigned current_row(0), current_column(0);
	for (unsigned i = 0; i < num_glyphs; i++)
	{
		const auto& glyph = glyph_bitmaps[i];
		for (unsigned h = 0; h < glyph.size.y; h++)
		{
			for (unsigned w = 0; w < glyph.size.x; w++)
			{
				auto offset = current_row * glyph_height * atlas_width
				              + current_column * glyph_width;
				atlas_pixels[offset + h * atlas_width + w] = glyph.pixels[h * glyph.size.x + w];
			}
		}

		GLfloat x_min = current_column * glyph_width / (GLfloat) atlas_width,
				x_max = (current_column * glyph_width + glyph.size.x) / (GLfloat) atlas_width,
				y_min = (atlas_height - current_row * glyph_height - glyph.size.y) / (GLfloat) atlas_height,
				y_max = (atlas_height - current_row * glyph_height) / (GLfloat) atlas_height;
		GLfloat texture_coords[] = {
				x_min, y_max,
				x_max, y_max,
				x_max, y_min,
				x_min, y_min
		};
		m_glyphs[i + s_first_char] = new Glyph(texture_coords, glyph.size, glyph.bearing, glyph.advance);


		if (++current_column >= atlas_glyphs_per_line)
		{
			current_column = 0;
			current_row++;
		}
	}

	// inverting all pixels vertically
	for (unsigned i = 0; i < atlas_height / 2; i++)
	{
		for (unsigned j = 0; j < atlas_width; j++)
			std::swap(atlas_pixels[i * atlas_width + j], atlas_pixels[(atlas_height - i - 1) * atlas_width + j]);
	}
	m_glyph_atlas = new Texture({ atlas_width, atlas_height }, atlas_pixels, GL_RED, GL_RED, true, std::string());
}

inline unsigned FontLoader::nextPowerOf2(unsigned x)
{
	unsigned num(1);
	while ((num = num << 1) < x);
	return num;
}
