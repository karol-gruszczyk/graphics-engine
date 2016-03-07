#include "rectangle.h"

using engine::Rectangle;


Rectangle::Rectangle()
{}

Rectangle::Rectangle(glm::vec2 size, glm::vec2 position /* =  { 0.f, 0.f } */, glm::vec2 pivot /* = { 0.f, 0.f } */)
{
	initialize(size, position, pivot);
}

void Rectangle::initialize(glm::vec2 size, glm::vec2 position /* =  { 0.f, 0.f } */, glm::vec2 pivot /* = { 0.f, 0.f } */)
{
	m_width = size.x;
	m_length = size.y;
	m_position = position;
	m_pivot = pivot;
	updateTranslationMatrix();

	GLfloat vertices[] = {
		0.f, 0.f,
		m_width, 0.f,
		m_width, m_length,
		0.f, m_length,
	};
	GLfloat texture_coords[] = {
		0.f, 1.f,
		1.f, 1.f,
		1.f, 0.f,
		0.f, 0.f
	};
	m_num_vertices = 4;

	glGenBuffers(1, &m_texture_coords_vbo_id);
	m_texture_coords_vbo_created = true;

	glGenBuffers(1, &m_vertex_vbo_id);
	m_vertex_vbo_created = true;

	glGenVertexArrays(1, &m_vao_id);
	m_vao_created = true;

	glBindVertexArray(m_vao_id);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertex_vbo_id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(VERTEX_ATTRIB_POINTER, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);
		glEnableVertexAttribArray(VERTEX_ATTRIB_POINTER);

		glBindBuffer(GL_ARRAY_BUFFER, m_texture_coords_vbo_id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(texture_coords), texture_coords, GL_STATIC_DRAW);
		glVertexAttribPointer(TEXTURE_COORD_ATTRIB_POINTER, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);
		glEnableVertexAttribArray(TEXTURE_COORD_ATTRIB_POINTER);
	glBindVertexArray(NULL);
}

void Rectangle::render()
{
	glBindVertexArray(m_vao_id);
	glDrawArrays(GL_TRIANGLE_FAN, 0, m_num_vertices);
	glBindVertexArray(NULL);
}
