#include <glm/gtc/matrix_transform.hpp>
#include "font.hpp"
#include "font_loader.hpp"
#include "engine/engine.hpp"
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
	font->m_glyphs = loader.getGlyphs();
	font->m_line_spacing = loader.getLineSpacing();
	font->m_glyph_atlas = loader.getGlyphAtlas();

	return font;
}

void Font::renderText(const std::string& text, glm::uvec2 position)
{
	s_shader->bind();
	glDisable(GL_CULL_FACE); // temporary, for dev purposes

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glm::mat4 cursor_position;
	glm::ivec2 advance = position;
	int line_num = 0;
	for (const auto& ch : text)
	{
		if (ch == '\n')
		{
			line_num++;
			advance = { position.x, position.y + line_num * m_line_spacing };
			cursor_position = glm::translate(glm::mat4(), glm::vec3(advance, 0));
			advance = { 0, 0 };
			continue;
		}
		auto offset = m_glyphs[ch]->getSize().y - m_glyphs[ch]->getBearing().y;
		advance.y += offset;
		cursor_position = glm::translate(cursor_position, glm::vec3(advance, 0.f));
		s_shader->setUniformMatrix4("model_matrix", cursor_position);
		m_glyphs[ch]->render();
		advance = m_glyphs[ch]->getAdvance() + glm::ivec2(0, -offset);
	}
	glDisable(GL_BLEND);
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
