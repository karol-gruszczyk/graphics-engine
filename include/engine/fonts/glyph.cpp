#include "glyph.hpp"


using engine::Glyph;


Glyph::Glyph(Texture* bitmap, const glm::uvec2& size, const glm::ivec2& bearing, const GLint& advance)
		: m_size(size), m_bitmap(bitmap), m_bearing(bearing), m_advance(advance)
{
	m_rect = new Rectangle({ (float) m_size.x, (float) m_size.y });
}

Glyph::~Glyph()
{
	delete m_bitmap;
	delete m_rect;
}

const glm::uvec2& Glyph::getSize() const
{
	return m_size;
}

const glm::ivec2& Glyph::getBearing() const
{
	return m_bearing;
}

const GLint& Glyph::getAdvance() const
{
	return m_advance;
}

void Glyph::render() const
{
	m_bitmap->bind();
	m_rect->render();
}
