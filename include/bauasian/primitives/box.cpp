#include "box.hpp"


using bauasian::Box;


Box::Box(const glm::vec3& size, const glm::vec3& position /* = { 0.f, 0.f, 0.f } */,
         const glm::vec3& rotation /* = { 0.f, 0.f, 0.f } */,
         const glm::vec3& scale /* = { 1.f, 1.f, 1.f } */, const glm::vec3& pivot /* = { 0.f, 0.f, 0.f } */)
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
	const unsigned floats_per_vertex = 3 + 3 + 2;
	m_num_vertices = 24;
	m_num_faces = 6;
	GLfloat vertex_data[] =  // position(3) | normal(3) | texture_coordinates(2)
			{
					// bottom
					0.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.f, 0.f,                    // 0
					m_width, 0.f, 0.f, 0.f, -1.f, 0.f, 1.f, 0.f,                // 1
					0.f, 0.f, m_length, 0.f, -1.f, 0.f, 0.f, 1.f,               // 3
					m_width, 0.f, m_length, 0.f, -1.f, 0.f, 1.f, 1.f,           // 2

					// up
					0.f, m_height, m_length, 0.f, 1.f, 0.f, 0.f, 0.f,           // 7
					m_width, m_height, m_length, 0.f, 1.f, 0.f, 1.f, 0.f,       // 6
					0.f, m_height, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f,                // 4
					m_width, m_height, 0.f, 0.f, 1.f, 0.f, 1.f, 1.f,            // 5

					// front
					m_width, m_height, m_length, 0.f, 0.f, 1.f, 1.f, 1.f,       // 6
					0.f, m_height, m_length, 0.f, 0.f, 1.f, 0.f, 1.f,           // 7
					m_width, 0.f, m_length, 0.f, 0.f, 1.f, 1.f, 0.f,            // 2
					0.f, 0.f, m_length, 0.f, 0.f, 1.f, 0.f, 0.f,                // 3

					// back
					0.f, 0.f, 0.f, 0.f, 0.f, -1.f, 1.f, 0.f,                    // 0
					0.f, m_height, 0.f, 0.f, 0.f, -1.f, 1.f, 1.f,               // 4
					m_width, 0.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.f,                // 1
					m_width, m_height, 0.f, 0.f, 0.f, -1.f, 0.f, 1.f,           // 5

					// left
					0.f, m_height, 0.f, -1.f, 0.f, 0.f, 0.f, 1.f,               // 4
					0.f, 0.f, 0.f, -1.f, 0.f, 0.f, 0.f, 0.f,                    // 0
					0.f, m_height, m_length, -1.f, 0.f, 0.f, 1.f, 1.f,          // 7
					0.f, 0.f, m_length, -1.f, 0.f, 0.f, 1.f, 0.f,               // 3

					// right
					m_width, m_height, 0.f, 1.f, 0.f, 0.f, 1.f, 1.f,            // 5
					m_width, m_height, m_length, 1.f, 0.f, 0.f, 0.f, 1.f,       // 6
					m_width, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f, 0.f,                 // 1
					m_width, 0.f, m_length, 1.f, 0.f, 0.f, 0.f, 0.f,            // 2
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
