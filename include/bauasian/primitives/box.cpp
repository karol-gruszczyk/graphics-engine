#include "box.hpp"


using bauasian::Box;


Box::Box(const glm::vec3& size)
		: Entity3D(GL_TRIANGLE_STRIP, 29, GL_UNSIGNED_SHORT, 24, 6), m_size(size)
{
	/* VERTICES:
	0.f, 0.f, 0.f,					// 0
	width, 0.f, 0.f,				// 1
	width, 0.f, length,			// 2
	0.f, 0.f, length,				// 3

	0.f, height, 0.f,				// 4
	width, height, 0.f,			// 5
	width, height, length,	// 6
	0.f, height, length			// 7
	*/
	const float& width(size.x), & length(size.y), & height(size.z);
	Vertex3D vertex_data[] =  // position(3) | normal(3) | texture_coordinates(2)
			{
					// bottom
					{{ 0.f,   0.f,    0.f },    { 0.f,  -1.f, 0.f },  { 0.f, 0.f }},    // 0
					{{ width, 0.f,    0.f },    { 0.f,  -1.f, 0.f },  { 1.f, 0.f }},    // 1
					{{ 0.f,   0.f,    length }, { 0.f,  -1.f, 0.f },  { 0.f, 1.f }},    // 3
					{{ width, 0.f,    length }, { 0.f,  -1.f, 0.f },  { 1.f, 1.f }},    // 2

					// up
					{{ 0.f,   height, length }, { 0.f,  1.f,  0.f },  { 0.f, 0.f }},    // 7
					{{ width, height, length }, { 0.f,  1.f,  0.f },  { 1.f, 0.f }},    // 6
					{{ 0.f,   height, 0.f },    { 0.f,  1.f,  0.f },  { 0.f, 1.f }},    // 4
					{{ width, height, 0.f },    { 0.f,  1.f,  0.f },  { 1.f, 1.f }},    // 5

					// front
					{{ width, height, length }, { 0.f,  0.f,  1.f },  { 1.f, 1.f }},    // 6
					{{ 0.f,   height, length }, { 0.f,  0.f,  1.f },  { 0.f, 1.f }},    // 7
					{{ width, 0.f,    length }, { 0.f,  0.f,  1.f },  { 1.f, 0.f }},    // 2
					{{ 0.f,   0.f,    length }, { 0.f,  0.f,  1.f },  { 0.f, 0.f }},    // 3

					// back
					{{ 0.f,   0.f,    0.f },    { 0.f,  0.f,  -1.f }, { 1.f, 0.f }},    // 0
					{{ 0.f,   height, 0.f },    { 0.f,  0.f,  -1.f }, { 1.f, 1.f }},    // 4
					{{ width, 0.f,    0.f },    { 0.f,  0.f,  -1.f }, { 0.f, 0.f }},    // 1
					{{ width, height, 0.f },    { 0.f,  0.f,  -1.f }, { 0.f, 1.f }},    // 5

					// left
					{{ 0.f,   height, 0.f },    { -1.f, 0.f,  0.f },  { 0.f, 1.f }},    // 4
					{{ 0.f,   0.f,    0.f },    { -1.f, 0.f,  0.f },  { 0.f, 0.f }},    // 0
					{{ 0.f,   height, length }, { -1.f, 0.f,  0.f },  { 1.f, 1.f }},    // 7
					{{ 0.f,   0.f,    length }, { -1.f, 0.f,  0.f },  { 1.f, 0.f }},    // 3

					// right
					{{ width, height, 0.f },    { 1.f,  0.f,  0.f },  { 1.f, 1.f }},    // 5
					{{ width, height, length }, { 1.f,  0.f,  0.f },  { 0.f, 1.f }},    // 6
					{{ width, 0.f,    0.f },    { 1.f,  0.f,  0.f },  { 1.f, 0.f }},    // 1
					{{ width, 0.f,    length }, { 1.f,  0.f,  0.f },  { 0.f, 0.f }},    // 2
			};
	GLushort indices[] =
			{
					0, 1, 2, 3, 0xFFFF,         // bottom
					4, 5, 6, 7, 0xFFFF,         // up
					8, 9, 10, 11, 0xFFFF,       // front
					12, 13, 14, 15, 0xFFFF,     // back
					16, 17, 18, 19, 0xFFFF,     // left
					20, 21, 22, 23              // right
			};
	calculateTangents(vertex_data, indices, sizeof(indices) / sizeof(indices[0]));

	updateVertexBuffer(sizeof(vertex_data), vertex_data, Entity3D::Vertex3D::offsets, GL_STATIC_DRAW);
	updateIndexBuffer(sizeof(indices), indices, GL_STATIC_DRAW);
}

const glm::vec3& Box::getSize() const
{
	return m_size;
}
