#include "font.hpp"
#include "font_loader.hpp"
#include "bauasian/bauasian.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>


using bauasian::Font;
using bauasian::ShaderProgram;

std::map<std::string, Font*> Font::s_fonts;
ShaderProgram* Font::s_shader = nullptr;

Font* Font::loadFromFile(const boost::filesystem::path& path, unsigned font_size)
{
	if (!boost::filesystem::exists(path))
		throw FileNotFoundException(path);

	getStaticInstance();  // called to initialize
	auto full_path = boost::filesystem::canonical(path).string();
	if (s_fonts.count(full_path))
		return s_fonts[full_path];

	Font* font = new Font();
	s_fonts[full_path] = font;

	FontLoader loader(path, font_size);
	font->m_glyphs = loader.getGlyphs();
	font->m_line_spacing = loader.getLineSpacing();
	font->m_glyph_atlas = loader.getGlyphAtlas();

	return font;
}

void Font::bind() const
{
	m_glyph_atlas->bind();
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
	const auto& shader_path = Bauasian::getInstance().getShaderPath();
	Shader vertexShader(shader_path / "fonts/font_vs.glsl", Shader::VERTEX_SHADER);
	Shader fragmentShader(shader_path / "fonts/font_fs.glsl", Shader::FRAGMENT_SHADER);
	s_shader = new ShaderProgram({ &vertexShader, &fragmentShader });
	updateContextSize();
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
