#include "text.hpp"


using engine::Text;

Text::Text(engine::Font* font)
	: m_font(font)
{
	glGenVertexArrays(1, &m_vao_id);

	glGenBuffers(1, &m_vbo_id);
	

	glBindVertexArray(0);
}

Text::~Text()
{
	glDeleteVertexArrays(1, &m_vao_id);
	glDeleteBuffers(1, &m_vbo_id);
}

const std::string& Text::getText() const
{
	return m_text;
}

void Text::setText(const std::string& text)
{
	m_text = text;
}

const glm::vec3& Text::getTextColor() const
{
	return m_text_color;
}

void Text::setTextColor(const glm::vec3& text_color)
{
	m_text_color = text_color;
}
