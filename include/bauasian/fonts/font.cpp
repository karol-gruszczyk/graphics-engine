#include "font.hpp"
#include "bauasian/bauasian.hpp"

#include <glm/gtc/matrix_transform.hpp>


using bauasian::Font;
using bauasian::ShaderProgram;
using bauasian::Texture;

ShaderProgram* Font::s_shader = nullptr;
GLint Font::m_location_projection_matrix;

Font::Font(const unsigned& font_size, const std::map<char, Glyph*>& glyphs, Texture* glyph_atlas,
           const int& line_spacing)
		: m_font_size(font_size), m_glyphs(glyphs), m_glyph_atlas(glyph_atlas), m_line_spacing(line_spacing)
{}

float Font::getScale(const unsigned int& font_size) const
{
	return font_size / (float) m_font_size;
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
}

void Font::loadShader()
{
	Shader* vertex_shader = new Shader("fonts/font_vs.glsl", Shader::VERTEX_SHADER);
	Shader* fragment_shader = new Shader("fonts/font_fs.glsl", Shader::FRAGMENT_SHADER);
	s_shader = new ShaderProgram({ vertex_shader, fragment_shader });
	delete vertex_shader;
	delete fragment_shader;
	m_location_projection_matrix = s_shader->getUniformLocation("projection_matrix");
}

void Font::unloadShader()
{
	if (s_shader)
		delete s_shader;
}

void Font::updateContextSize()
{
	const auto& size = getContextSize();
	s_shader->setUniform(m_location_projection_matrix, glm::ortho(0.f, (float) size.x, (float) size.y, 0.f));
}
