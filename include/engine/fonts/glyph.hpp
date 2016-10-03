#ifndef GRAPHICS_ENGINE_GLYPH_HPP
#define GRAPHICS_ENGINE_GLYPH_HPP

#include <glm/glm.hpp>
#include "engine/materials/texture.hpp"
#include "engine/primitives/rectangle.hpp"


namespace engine
{
	class Glyph;
}

class engine::Glyph
{
public:
	Glyph(const GLfloat* const texture_coords, const glm::uvec2& size, const glm::ivec2& bearing,
	      const glm::ivec2& advance);
	~Glyph();

	const glm::ivec2& getAdvance() const;
	const GLfloat* const getPositions() const;
	const GLfloat* const getTextureCoords() const;

private:
	glm::ivec2 m_advance;
	GLfloat m_positions[8];
	GLfloat* m_texture_coords;
};

#endif /* GRAPHICS_ENGINE_GLYPH_HPP */
