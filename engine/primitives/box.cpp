#include "box.h"

#define ELEMENTS_BUFFER_LENGTH 29

using engine::Box;


Box::Box(glm::vec3 size, glm::vec3 position /* = { 0.f, 0.f, 0.f } */, glm::vec3 rotation /* = { 0.f, 0.f, 0.f } */,
	glm::vec3 scale /* = { 1.f, 1.f, 1.f } */, glm::vec3 pivot /* = { 0.f, 0.f, 0.f } */)
	: Entity3D(position, rotation, scale, pivot),
	m_width(size.x), m_length(size.y), m_height(size.z)
{
	/* VERTIVES:
	0.f, 0.f, 0.f,					// 0
	m_width, 0.f, 0.f,				// 1
	m_width, 0.f, m_length,			// 2
	0.f, 0.f, m_length,				// 3

	0.f, m_height, 0.f,				// 4
	m_width, m_height, 0.f,			// 5
	m_width, m_height, m_length,	// 6
	0.f, m_height, m_length			// 7
	*/

	GLfloat positions[] =
	{
		// bottom
		0.f, 0.f, 0.f,					// - 0
		m_width, 0.f, 0.f,				// - 1
		0.f, 0.f, m_length,				// - 3
		m_width, 0.f, m_length,			// - 2

		// up
		0.f, m_height, m_length,		// 4 - 7
		m_width, m_height, m_length,	// 5 - 6
		0.f, m_height, 0.f,				// 6 - 4
		m_width, m_height, 0.f,			// 7 - 5

		// front
		m_width, m_height, m_length,	// 8 - 6
		0.f, m_height, m_length,		// 9 - 7
		m_width, 0.f, m_length,			// 10 - 2
		0.f, 0.f, m_length,				// 11 - 3

		// back
		0.f, 0.f, 0.f,					// 12 - 0
		0.f, m_height, 0.f,				// 14 - 4
		m_width, 0.f, 0.f,				// 13 - 1
		m_width, m_height, 0.f,			// 15 - 5

		// left
		0.f, m_height, 0.f,				// 16 - 4
		0.f, 0.f, 0.f,					// 17 - 0
		0.f, m_height, m_length,		// 18 - 7
		0.f, 0.f, m_length,				// 19 - 3

		// right
		m_width, m_height, 0.f,			// 20 - 5
		m_width, m_height, m_length,	// 21 - 6
		m_width, 0.f, 0.f,				// 22 - 1
		m_width, 0.f, m_length,			// 23 - 2
	};
	GLfloat texture_coords[] =
	{
		// bottom
		0.f, 0.f,
		1.f, 0.f,
		0.f, 1.f,
		1.f, 1.f,

		// up
		0.f, 0.f,
		1.f, 0.f,
		0.f, 1.f,
		1.f, 1.f,

		// front
		1.f, 1.f,
		0.f, 1.f,
		1.f, 0.f,
		0.f, 0.f,

		// back
		1.f, 0.f,
		1.f, 1.f,
		0.f, 0.f,
		0.f, 1.f,

		// left
		0.f, 1.f,
		0.f, 0.f,
		1.f, 1.f,
		1.f, 0.f,

		// right
		1.f, 1.f,
		0.f, 1.f,
		1.f, 0.f,
		0.f, 0.f
	};
	GLfloat normals[] =
	{
		// bottom
		0.f, -1.f, 0.f,
		0.f, -1.f, 0.f,
		0.f, -1.f, 0.f,
		0.f, -1.f, 0.f,

		// up
		0.f, 1.f, 0.f,
		0.f, 1.f, 0.f,
		0.f, 1.f, 0.f,
		0.f, 1.f, 0.f,

		// front
		0.f, 0.f, 1.f,
		0.f, 0.f, 1.f,
		0.f, 0.f, 1.f,
		0.f, 0.f, 1.f,

		// back
		0.f, 0.f, -1.f,
		0.f, 0.f, -1.f,
		0.f, 0.f, -1.f,
		0.f, 0.f, -1.f,

		// left
		-1.f, 0.f, 0.f,
		-1.f, 0.f, 0.f,
		-1.f, 0.f, 0.f,
		-1.f, 0.f, 0.f,

		// right
		1.f, 0.f, 0.f,
		1.f, 0.f, 0.f,
		1.f, 0.f, 0.f,
		1.f, 0.f, 0.f
	};

	GLushort indices[] =
	{
		0, 1, 2, 3, 0xFFFF,		// bottom
		4, 5, 6, 7, 0xFFFF,		// up
		8, 9, 10, 11, 0xFFFF,	// front
		12, 13, 14, 15, 0xFFFF, // back
		16, 17, 18, 19, 0xFFFF, // left
		20, 21, 22, 23			// right
	};

	glBindVertexArray(m_vao_id);
		createBufferObject(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
		glVertexAttribPointer(POSITION_ATTRIB_POINTER, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
		glEnableVertexAttribArray(POSITION_ATTRIB_POINTER);

		createBufferObject(GL_ARRAY_BUFFER, sizeof(texture_coords), texture_coords, GL_STATIC_DRAW);
		glVertexAttribPointer(TEXTURE_COORD_ATTRIB_POINTER, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);
		glEnableVertexAttribArray(TEXTURE_COORD_ATTRIB_POINTER);

		createBufferObject(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);
		glVertexAttribPointer(NORMAL_ATTRIB_POINTER, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
		glEnableVertexAttribArray(NORMAL_ATTRIB_POINTER);

		createBufferObject(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glEnable(GL_PRIMITIVE_RESTART);
		glPrimitiveRestartIndex(0xFFFF);
	glBindVertexArray(NULL);
}

void engine::Box::render()
{
	glBindVertexArray(m_vao_id);
	glDrawElements(GL_TRIANGLE_STRIP, ELEMENTS_BUFFER_LENGTH, GL_UNSIGNED_SHORT, nullptr);
	glBindVertexArray(NULL);
}
