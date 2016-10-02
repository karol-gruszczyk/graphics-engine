#include "text.hpp"


using engine::Text;

Text::Text(engine::Font* font, const std::string& text /* = "" */, const glm::vec3& color /* = { 0.f, 0.f, 0.f } */)
		: Entity2D({ 0.f, 0.f }), m_font(font), m_text(text), m_color(color)
{
	GLfloat positions[] = {
			0.f, 0.f,
			50.f, 0.f,
			50.f, 100.f,
			0.f, 100.f,
	};
	GLfloat texture_coords[] = {
			0.f, 1.f,
			1.f, 1.f,
			1.f, 0.f,
			0.f, 0.f
	};
	GLushort indices[] =
			{
					1, 0, 2, 3
			};

	setupRendering(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT);

	glBindVertexArray(m_vao_id);
	createBufferObject(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
	glVertexAttribPointer(POSITION_ATTRIB_POINTER, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);
	glEnableVertexAttribArray(POSITION_ATTRIB_POINTER);

	createBufferObject(GL_ARRAY_BUFFER, sizeof(texture_coords), texture_coords, GL_STATIC_DRAW);
	glVertexAttribPointer(TEXTURE_COORD_ATTRIB_POINTER, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);
	glEnableVertexAttribArray(TEXTURE_COORD_ATTRIB_POINTER);

	createBufferObject(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindVertexArray(0);
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
	return m_color;
}

void Text::setTextColor(const glm::vec3& text_color)
{
	m_color = text_color;
}

void Text::render() const
{
	m_font->bind();
	Entity2D::render();
}
