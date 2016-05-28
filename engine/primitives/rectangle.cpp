#include "rectangle.h"

#define ELEMENTS_BUFFER_LENGTH 4

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

	GLfloat positions[] = {
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
	GLushort indices[] =
	{
		1, 0, 2, 3 
	};

	Entity2D::initBuffers();

	static_assert(2 * sizeof(GLfloat) % 4 == 0, "Buffer data should be aligned in 4 byte blocks");

	glBindVertexArray(m_vao_id);
		createBufferObject(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
		glVertexAttribPointer(POSITION_ATTRIB_POINTER, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);
		glEnableVertexAttribArray(POSITION_ATTRIB_POINTER);

		createBufferObject(GL_ARRAY_BUFFER, sizeof(texture_coords), texture_coords, GL_STATIC_DRAW);
		glVertexAttribPointer(TEXTURE_COORD_ATTRIB_POINTER, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);
		glEnableVertexAttribArray(TEXTURE_COORD_ATTRIB_POINTER);

		createBufferObject(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindVertexArray(NULL);
}

void Rectangle::render()
{
	glBindVertexArray(m_vao_id);
	glDrawElements(GL_TRIANGLE_STRIP, ELEMENTS_BUFFER_LENGTH, GL_UNSIGNED_SHORT, nullptr);
	glBindVertexArray(NULL);
}
