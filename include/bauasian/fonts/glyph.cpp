#include "glyph.hpp"


using bauasian::Glyph;


Glyph::Glyph(const GLfloat* const texture_coords, const glm::uvec2& size, const glm::ivec2& bearing,
             const glm::ivec2& advance)
		: m_advance(advance)
{
	glm::vec2 offset = { bearing.x, -bearing.y };
	m_positions[0] = offset.x;
	m_positions[1] = offset.y;
	m_positions[2] = (float) size.x + offset.x;
	m_positions[3] = offset.y;
	m_positions[4] = (float) size.x + offset.x;
	m_positions[5] = (float) size.y + offset.y;
	m_positions[6] = offset.x;
	m_positions[7] = (float) size.y + offset.y;

	m_texture_coords = new GLfloat[8];
	std::memcpy(m_texture_coords, texture_coords, sizeof(GLfloat) * 8);
}

Glyph::~Glyph()
{
	delete[] m_texture_coords;
}

const glm::ivec2& Glyph::getAdvance() const
{
	return m_advance;
}

const GLfloat* const Glyph::getPositions() const
{
	return m_positions;
}

const GLfloat* const Glyph::getTextureCoords() const
{
	return m_texture_coords;
}
