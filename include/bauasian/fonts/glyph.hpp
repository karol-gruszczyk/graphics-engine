#ifndef BAUASIAN_GLYPH_HPP
#define BAUASIAN_GLYPH_HPP

#include "bauasian/materials/texture.hpp"
#include "bauasian/primitives/rectangle.hpp"

#include <glm/glm.hpp>


namespace bauasian
{
	class Glyph;
}

class bauasian::Glyph
{
public:
	Glyph(const GLfloat* const texture_coords, const glm::uvec2& size, const glm::ivec2& bearing,
	      const glm::ivec2& advance);

	const glm::ivec2& getAdvance() const;
	const GLfloat* const getPositions() const;

private:
	glm::ivec2 m_advance;
	GLfloat m_positions[16];
};

#endif /* BAUASIAN_GLYPH_HPP */
