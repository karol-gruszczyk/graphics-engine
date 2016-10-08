#include "text.hpp"

#include <glm/gtc/matrix_transform.hpp>


using bauasian::Text;

Text::Text(bauasian::Font* font, const std::string& text /* = "" */, const unsigned& font_size /* = 0 */
		, const glm::vec3& color /* = { 0.f, 0.f, 0.f } */)
		: Entity2D(GL_TRIANGLE_STRIP, 0, GL_UNSIGNED_INT), m_font(font), m_text(text), m_color(color)
{
	setFontSize(font_size ?: m_font->m_font_size);
	updateBufferObjects();

	m_location_text_color = m_font->s_shader->getUniformLocation("text_color");
	m_location_model_matrix = m_font->s_shader->getUniformLocation("model_matrix");
}

const std::string& Text::getText() const
{
	return m_text;
}

void Text::setText(const std::string& text)
{
	m_text = text;
	updateBufferObjects();
}

const glm::vec3& Text::getTextColor() const
{
	return m_color;
}

void Text::setTextColor(const glm::vec3& text_color)
{
	m_color = text_color;
}

const unsigned& Text::getFontSize() const
{
	return m_font_size;
}

void Text::setFontSize(const unsigned& font_size)
{
	m_font_size = font_size;
	setScale({ 1.f, 1.f });
}

void Text::setScale(const glm::vec2& scale)
{
	const auto& font_scale = m_font->getScale(m_font_size);
	Entity2D::setScale(scale * glm::vec2(font_scale));
}

void Text::render() const
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	m_font->bind();
	m_font->s_shader->setUniform(m_location_text_color, m_color);
	m_font->s_shader->setUniform(m_location_model_matrix, m_model_matrix);
	glEnable(GL_PRIMITIVE_RESTART);
	glPrimitiveRestartIndex(0xFFFFFFFF);
	Renderable::render();
	glDisable(GL_PRIMITIVE_RESTART);
	glDisable(GL_BLEND);
}

void Text::updateBufferObjects()
{
	const unsigned short floats_per_glyph = 16;
	unsigned num_vertices_data_floats = (unsigned) m_text.size() * floats_per_glyph;
	GLfloat* vertices_data = new GLfloat[num_vertices_data_floats];
	unsigned num_indices = (unsigned) m_text.size() * 5;
	GLuint* indices = new GLuint[num_indices];

	glm::vec2 advance = { 0.f, 0.f };
	unsigned i = 0;
	for (const auto& c : m_text)
	{
		if (c == '\n')
		{
			advance = { 0.f, advance.y + m_font->m_line_spacing };
			continue;
		}
		const auto& glyph = m_font->m_glyphs[c];
		std::memcpy(vertices_data + i * floats_per_glyph, glyph->getPositions(), sizeof(GLfloat) * floats_per_glyph);
		for (unsigned j = 0; j < 4; j++)
		{
			vertices_data[i * floats_per_glyph + j * 4 + 0] += advance.x;
			vertices_data[i * floats_per_glyph + j * 4 + 1] += advance.y;
		}
		advance += glyph->getAdvance();

		indices[i * 5 + 0] = i * 4 + 1;
		indices[i * 5 + 1] = i * 4 + 0;
		indices[i * 5 + 2] = i * 4 + 2;
		indices[i * 5 + 3] = i * 4 + 3;
		indices[i * 5 + 4] = 0xFFFFFFFF;
		i++;
	}
	m_elements_count = num_indices;

	glBindVertexArray(m_vao_id);
	updateVertexBuffer(sizeof(GLfloat) * num_vertices_data_floats, vertices_data, { 4 }, GL_DYNAMIC_DRAW);
	updateIndexBuffer(sizeof(GLuint) * num_indices, indices, GL_DYNAMIC_DRAW);

	delete[] vertices_data;
	delete[] indices;
}
