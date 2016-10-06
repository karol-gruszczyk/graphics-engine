#include "text.hpp"

#include <glm/gtc/matrix_transform.hpp>


using bauasian::Text;

Text::Text(bauasian::Font* font, const std::string& text /* = "" */, const glm::vec3& color /* = { 0.f, 0.f, 0.f } */)
		: m_font(font), m_text(text), m_color(color)
{
	GLuint vbo[2];
	glGenBuffers(2, vbo);
	for (short i = 0; i < 2; i++)
		m_vbos.push_back(vbo[i]);

	setupRendering(GL_TRIANGLE_STRIP, 0, GL_UNSIGNED_INT);
	updateBufferObjects();
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

void Text::render() const
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	m_font->bind();
	m_font->s_shader->setUniformVector3("text_color", m_color);
	m_font->s_shader->setUniformMatrix4("model_matrix", glm::translate(glm::mat4(), glm::vec3(m_position, 0.f)));
	glEnable(GL_PRIMITIVE_RESTART);
	glPrimitiveRestartIndex(0xFFFFFFFF);
	glBindVertexArray(m_vao_id);
	glDrawElements(m_draw_mode, m_indices_size, m_elements_type, nullptr);
	glBindVertexArray(0);
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
	m_indices_size = num_indices;

	glBindVertexArray(m_vao_id);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbos[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * num_vertices_data_floats, vertices_data, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(POSITION_ATTRIB_POINTER, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), nullptr);
	glEnableVertexAttribArray(POSITION_ATTRIB_POINTER);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vbos[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * num_indices, indices, GL_DYNAMIC_DRAW);

	glBindVertexArray(0);

	delete[] vertices_data;
	delete[] indices;
}
