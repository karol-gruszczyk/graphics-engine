#include "box.hpp"


using bauasian::Box;


Box::Box(const glm::vec3& size)
		: m_size(size)
{
	m_num_vertices = 24;
	m_num_faces = 6;
	const unsigned floats_per_vertex = 3 + 3 + 2;
	/* VERTIVES:
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
	GLfloat vertex_data[] =  // position(3) | normal(3) | texture_coordinates(2)
			{
					// bottom
					0.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.f, 0.f,                    // 0
					width, 0.f, 0.f, 0.f, -1.f, 0.f, 1.f, 0.f,                // 1
					0.f, 0.f, length, 0.f, -1.f, 0.f, 0.f, 1.f,               // 3
					width, 0.f, length, 0.f, -1.f, 0.f, 1.f, 1.f,           // 2

					// up
					0.f, height, length, 0.f, 1.f, 0.f, 0.f, 0.f,           // 7
					width, height, length, 0.f, 1.f, 0.f, 1.f, 0.f,       // 6
					0.f, height, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f,                // 4
					width, height, 0.f, 0.f, 1.f, 0.f, 1.f, 1.f,            // 5

					// front
					width, height, length, 0.f, 0.f, 1.f, 1.f, 1.f,       // 6
					0.f, height, length, 0.f, 0.f, 1.f, 0.f, 1.f,           // 7
					width, 0.f, length, 0.f, 0.f, 1.f, 1.f, 0.f,            // 2
					0.f, 0.f, length, 0.f, 0.f, 1.f, 0.f, 0.f,                // 3

					// back
					0.f, 0.f, 0.f, 0.f, 0.f, -1.f, 1.f, 0.f,                    // 0
					0.f, height, 0.f, 0.f, 0.f, -1.f, 1.f, 1.f,               // 4
					width, 0.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.f,                // 1
					width, height, 0.f, 0.f, 0.f, -1.f, 0.f, 1.f,           // 5

					// left
					0.f, height, 0.f, -1.f, 0.f, 0.f, 0.f, 1.f,               // 4
					0.f, 0.f, 0.f, -1.f, 0.f, 0.f, 0.f, 0.f,                    // 0
					0.f, height, length, -1.f, 0.f, 0.f, 1.f, 1.f,          // 7
					0.f, 0.f, length, -1.f, 0.f, 0.f, 1.f, 0.f,               // 3

					// right
					width, height, 0.f, 1.f, 0.f, 0.f, 1.f, 1.f,            // 5
					width, height, length, 1.f, 0.f, 0.f, 0.f, 1.f,       // 6
					width, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f, 0.f,                 // 1
					width, 0.f, length, 1.f, 0.f, 0.f, 0.f, 0.f,            // 2
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

	setupRendering(GL_TRIANGLE_STRIP, 29, GL_UNSIGNED_SHORT);

	glBindVertexArray(m_vao_id);
	createBufferObject(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
	glVertexAttribPointer(POSITION_ATTRIB_POINTER, 3, GL_FLOAT, GL_FALSE,
	                      floats_per_vertex * sizeof(GLfloat), nullptr);
	glEnableVertexAttribArray(POSITION_ATTRIB_POINTER);

	glVertexAttribPointer(NORMAL_ATTRIB_POINTER, 3, GL_FLOAT, GL_FALSE,
	                      floats_per_vertex * sizeof(GLfloat), (void*) (sizeof(GLfloat) * 3));
	glEnableVertexAttribArray(NORMAL_ATTRIB_POINTER);

	glVertexAttribPointer(TEXTURE_COORD_ATTRIB_POINTER, 2, GL_FLOAT, GL_FALSE,
	                      floats_per_vertex * sizeof(GLfloat), (void*) (sizeof(GLfloat) * 6));
	glEnableVertexAttribArray(TEXTURE_COORD_ATTRIB_POINTER);

	createBufferObject(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void Box::render() const
{
	glEnable(GL_PRIMITIVE_RESTART);
	glPrimitiveRestartIndex(0xFFFF);
	Entity3D::render();
	glDisable(GL_PRIMITIVE_RESTART);
}

const glm::vec3& Box::getSize() const
{
	return m_size;
}
