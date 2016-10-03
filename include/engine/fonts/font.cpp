#include "font.hpp"
#include "font_loader.hpp"
#include "engine/engine.hpp"
#include "engine/shaders/vertex_shader.hpp"
#include "engine/shaders/fragment_shader.hpp"
#include <glm/gtc/matrix_transform.hpp>


using engine::Font;
using engine::ShaderProgram;

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
	const auto& shader_path = Engine::getInstance().getShaderPath();
	VertexShader vertexShader(shader_path / "fonts/font_vs.glsl");
	FragmentShader fragmentShader(shader_path / "fonts/font_fs.glsl");
	s_shader = new ShaderProgram({ &vertexShader, &fragmentShader });
	s_shader->setUniformMatrix4("projection_matrix", glm::ortho(0.f, 800.f, 600.f, 0.f));
}

void Font::unloadShader()
{
	if (s_shader)
		delete s_shader;
}
