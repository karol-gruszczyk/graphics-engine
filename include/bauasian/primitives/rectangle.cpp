#include "rectangle.hpp"


using bauasian::Rectangle;


Rectangle::Rectangle(const glm::vec2& size)
		: m_width(size.x), m_length(size.y)
{
	m_num_vertices = 4;
	m_num_faces = 2;
	GLfloat vertex_data[][2][2] = {
			{{ 0.f,     0.f },      { 0.f, 1.f }},
			{{ m_width, 0.f },      { 1.f, 1.f }},
			{{ m_width, m_length }, { 1.f, 0.f }},
			{{ 0.f,     m_length }, { 0.f, 0.f }},
	};
	GLushort indices[] =
			{
					1, 0, 2, 3
			};

	setupRendering(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT);

	glBindVertexArray(m_vao_id);
	createBufferObject(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
	glVertexAttribPointer(POSITION_ATTRIB_POINTER, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), nullptr);
	glEnableVertexAttribArray(POSITION_ATTRIB_POINTER);

	createBufferObject(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindVertexArray(0);
}
