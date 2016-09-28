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
	Glyph(Texture* bitmap, const glm::uvec2& size, const glm::ivec2& bearing, const GLint& advance);
	~Glyph();

	const glm::uvec2& getSize() const;
	const glm::ivec2& getBearing() const;
	const GLint& getAdvance() const;
	void render() const;
private:
	Texture* m_bitmap;
	glm::uvec2 m_size;
	glm::ivec2 m_bearing;
	GLint m_advance;
	Rectangle* m_rect;
};

#endif /* GRAPHICS_ENGINE_GLYPH_HPP */
