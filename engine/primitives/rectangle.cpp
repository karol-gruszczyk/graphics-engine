#include "rectangle.h"

using engine::Rectangle;

Rectangle::Rectangle(GLfloat width, GLfloat length)
{
	initialize(width, length);
}

void Rectangle::initialize(GLfloat width, GLfloat length)
{
	m_width = width;
	m_length = length;

	GLfloat vertices[] = {
		0.f, 0.f,
		width, 0.f,
		width, length,
		0.f, length,
	};
	m_num_vertices = 4;

	glGenBuffers(1, &m_vertex_vbo_id);
	m_vertex_vbo_initialized = true;

	glGenVertexArrays(1, &m_vao_id);
	m_vao_initialized = true;

	glBindVertexArray(m_vao_id);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertex_vbo_id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(VERTEX_ATTRIB_POINTER, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);
		glEnableVertexAttribArray(VERTEX_ATTRIB_POINTER);
	glBindVertexArray(NULL);
}

void Rectangle::render()
{
	glBindVertexArray(m_vao_id);
	glDrawArrays(GL_TRIANGLE_FAN, 0, m_num_vertices);
	glBindVertexArray(NULL);
}
