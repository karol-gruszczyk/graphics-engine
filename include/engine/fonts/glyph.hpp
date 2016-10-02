#ifndef GRAPHICS_ENGINE_GLYPH_HPP
#define GRAPHICS_ENGINE_GLYPH_HPP

#include <glm/glm.hpp>
#include "engine/materials/texture.hpp"
#include "engine/primitives/rectangle.hpp"


namespace engine
{
	class Glyph;
}

class engine::Glyph : public Entity2D
{
public:
	Glyph(const GLfloat* const texture_coords, const glm::uvec2& size, const glm::ivec2& bearing,
	      const glm::ivec2& advance);

	const glm::uvec2& getSize() const;
	const glm::ivec2& getBearing() const;
	const glm::ivec2& getAdvance() const;

private:
	glm::uvec2 m_size;
	glm::ivec2 m_bearing;
	glm::ivec2 m_advance;
};

#endif /* GRAPHICS_ENGINE_GLYPH_HPP */
