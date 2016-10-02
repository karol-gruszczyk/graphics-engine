#include "glyph.hpp"


using engine::Glyph;


Glyph::Glyph(const GLfloat* const texture_coords, const glm::uvec2& size, const glm::ivec2& bearing,
             const glm::ivec2& advance)
		: Entity2D({ 0.f, 0.f }), m_size(size), m_bearing(bearing), m_advance(advance)
{
	glm::vec2 offset = { m_bearing.x, -m_bearing.y };
	GLfloat positions[] = {
			0.f + offset.x, 0.f + offset.y,
			(float) m_size.x + offset.x, 0.f + offset.y,
			(float) m_size.x + offset.x, (float) m_size.y + offset.y,
			0.f + offset.x, (float) m_size.y + offset.y,
	};

	GLushort indices[] = {
			1, 0, 2, 3
	};

	setupRendering(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT);

	glBindVertexArray(m_vao_id);
	createBufferObject(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
	glVertexAttribPointer(POSITION_ATTRIB_POINTER, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);
	glEnableVertexAttribArray(POSITION_ATTRIB_POINTER);

	createBufferObject(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8, texture_coords, GL_STATIC_DRAW);
	glVertexAttribPointer(TEXTURE_COORD_ATTRIB_POINTER, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);
	glEnableVertexAttribArray(TEXTURE_COORD_ATTRIB_POINTER);

	createBufferObject(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindVertexArray(0);
}

const glm::uvec2& Glyph::getSize() const
{
	return m_size;
}

const glm::ivec2& Glyph::getBearing() const
{
	return m_bearing;
}

const glm::ivec2& Glyph::getAdvance() const
{
	return m_advance;
}
