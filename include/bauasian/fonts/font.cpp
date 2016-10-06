#include "font.hpp"
#include "font_loader.hpp"
#include "bauasian/bauasian.hpp"

#include <glm/gtc/matrix_transform.hpp>


using bauasian::Font;
using bauasian::ShaderProgram;

std::map<std::tuple<std::string, unsigned>, Font*> Font::s_fonts;
ShaderProgram* Font::s_shader = nullptr;

Font* Font::loadFromFile(const boost::filesystem::path& path, unsigned font_size /* = 48 */)
{
	if (!boost::filesystem::exists(path))
		throw FileNotFoundException(path);

	getStaticInstance();  // called to initialize
	auto key = std::make_tuple(boost::filesystem::canonical(path).string(), font_size);
	if (s_fonts.count(key))
		return s_fonts[key];

	Font* font = new Font();
	s_fonts[key] = font;

	FontLoader loader(path, font_size);
	font->m_font_size = font_size;
	font->m_glyphs = loader.getGlyphs();
	font->m_line_spacing = loader.getLineSpacing();
	font->m_glyph_atlas = loader.getGlyphAtlas();

	return font;
}

float Font::getScale(const unsigned int& font_size) const
{
	return font_size / (float)m_font_size;
}

void Font::bind() const
{
	m_glyph_atlas->bind();
	s_shader->use();
}

void Font::unbind() const
{
	m_glyph_atlas->unbind();
}

Font::~Font()
{
	for (const auto& glyph : m_glyphs)
		delete glyph.second;
	if (m_glyph_atlas)
		delete m_glyph_atlas;

	if (m_is_static_instance)
	{
		for (const auto& font : s_fonts)
			delete font.second;
		unloadShader();
	}
}

Font::Font()
{
	loadShader();
}

Font& Font::getStaticInstance()
{
	static Font instance;
	instance.m_is_static_instance = true;
	return instance;
}

void Font::loadShader()
{
	Shader* vertex_shader = new Shader("fonts/font_vs.glsl", Shader::VERTEX_SHADER);
	Shader* fragment_shader = new Shader("fonts/font_fs.glsl", Shader::FRAGMENT_SHADER);
	s_shader = new ShaderProgram({ vertex_shader, fragment_shader });
	updateContextSize();
	delete vertex_shader;
	delete fragment_shader;
}

void Font::unloadShader()
{
	if (s_shader)
		delete s_shader;
}

void Font::updateContextSize()
{
	const auto& size = getContextSize();
	s_shader->setUniformMatrix4("projection_matrix", glm::ortho(0.f, (float) size.x, (float) size.y, 0.f));
}
