#include "font.hpp"
#include "font_loader.hpp"
#include "engine/config.hpp"
#include "engine/primitives/rectangle.hpp"
#include "engine/shaders/vertex_shader.hpp"
#include "engine/shaders/fragment_shader.hpp"


using engine::Font;
using engine::ShaderProgram;

std::map<std::string, Font*> Font::s_fonts;
ShaderProgram* Font::s_shader = nullptr;

Font* Font::loadFromFile(const boost::filesystem::path& path)
{
	if (!boost::filesystem::exists(path))
		throw FileNotFoundException(path);

	getStaticInstance();  // called to initialize
	auto full_path = boost::filesystem::canonical(path).string();
	if (s_fonts.count(full_path))
		return s_fonts[full_path];

	Font* font = new Font();
	s_fonts[full_path] = font;

	FontLoader loader(path);
	font->m_glyph_bitmaps = loader.getGlyphs();

	return font;
}

void Font::renderText(const std::string& text)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	Rectangle rect({ 200.f, 200.f });
	m_glyph_bitmaps['X']->bind();
	rect.render();
	glDisable(GL_BLEND);
}

Font::~Font()
{
	for (const auto& glyph : m_glyph_bitmaps)
		delete glyph.second;

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
	const auto& shader_path = Config::getInstance().getShaderPath();
	VertexShader vertexShader(shader_path / "fonts/font_vs.glsl");
	FragmentShader fragmentShader(shader_path / "fonts/font_fs.glsl");
	s_shader = new ShaderProgram({&vertexShader, &fragmentShader});
}

void Font::unloadShader()
{
	if (s_shader)
		delete s_shader;
}
