#include "rectangle.hpp"


using bauasian::Rectangle;


Rectangle::Rectangle(const glm::vec2& size)
		: Entity2D(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT), m_width(size.x), m_length(size.y)
{
	Vertex2D vertex_data[] = {
			{{ 0.f,     0.f },      { 0.f, 1.f }},
			{{ m_width, 0.f },      { 1.f, 1.f }},
			{{ m_width, m_length }, { 1.f, 0.f }},
			{{ 0.f,     m_length }, { 0.f, 0.f }},
	};
	GLushort indices[] =
			{
					1, 0, 2, 3
			};

	updateVertexBuffer(sizeof(vertex_data), vertex_data, { 4 }, GL_STATIC_DRAW);
	updateIndexBuffer(sizeof(indices), indices, GL_STATIC_DRAW);
}
