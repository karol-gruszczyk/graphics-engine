#include "plane.hpp"


using bauasian::Plane;


Plane::Plane(const glm::vec2& size, unsigned tile /* = 1 */)
		: Entity3D(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, 4, 2), m_size(size), m_tile(tile)
{
	const float& width(size.x), & height(size.y);
	Vertex3D vertex_data[] = // position(3) | normal(3) | texture_coordinates(2)
			{
					{{ 0.f,   0.f, 0.f },    { 0.f, 1.f, 0.f }, { 0.f,          1.f * m_tile }},
					{{ 0.f,   0.f, height }, { 0.f, 1.f, 0.f }, { 0.f,          0.f }},
					{{ width, 0.f, 0.f },    { 0.f, 1.f, 0.f }, { 1.f * m_tile, 1.f * m_tile }},
					{{ width, 0.f, height }, { 0.f, 1.f, 0.f }, { 1.f * m_tile, 0.f }},
			};
	GLushort indices[] =
			{
					0, 1, 2, 3
			};
	calculateTangents(vertex_data, indices, 4);

	updateVertexBuffer(sizeof(vertex_data), vertex_data, Entity3D::Vertex3D::offsets, GL_STATIC_DRAW);
	updateIndexBuffer(sizeof(indices), indices, GL_STATIC_DRAW);
}
