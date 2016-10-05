#include "glyph.hpp"


using bauasian::Glyph;


Glyph::Glyph(const GLfloat* const texture_coords, const glm::uvec2& size, const glm::ivec2& bearing,
             const glm::ivec2& advance)
		: m_advance(advance)
{
	glm::vec2 offset = { bearing.x, -bearing.y };
	m_positions[0] = offset.x;
	m_positions[1] = offset.y;
	m_positions[2] = texture_coords[0];
	m_positions[3] = texture_coords[1];

	m_positions[4] = (float) size.x + offset.x;
	m_positions[5] = offset.y;
	m_positions[6] = texture_coords[2];
	m_positions[7] = texture_coords[3];

	m_positions[8] = (float) size.x + offset.x;
	m_positions[9] = (float) size.y + offset.y;
	m_positions[10] = texture_coords[4];
	m_positions[11] = texture_coords[5];

	m_positions[12] = offset.x;
	m_positions[13] = (float) size.y + offset.y;
	m_positions[14] = texture_coords[6];
	m_positions[15] = texture_coords[7];
}

const glm::ivec2& Glyph::getAdvance() const
{
	return m_advance;
}

const GLfloat* const Glyph::getPositions() const
{
	return m_positions;
}
