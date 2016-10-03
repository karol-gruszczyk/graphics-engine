#include "rectangle.hpp"


using bauasian::Rectangle;


Rectangle::Rectangle(const glm::vec2& size, const glm::vec2& position /* =  { 0.f, 0.f } */,
                     const glm::vec2& pivot /* = { 0.f, 0.f } */,
                     const GLfloat& rotation /* = 0.f */, const glm::vec2& scale /* = { 1.f, 1.f } */)
		: Entity2D(position, rotation, scale, pivot),
		  m_width(size.x), m_length(size.y)
{
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

	setupRendering(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT);

	glBindVertexArray(m_vao_id);
	createBufferObject(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
	glVertexAttribPointer(POSITION_ATTRIB_POINTER, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);
	glEnableVertexAttribArray(POSITION_ATTRIB_POINTER);

	createBufferObject(GL_ARRAY_BUFFER, sizeof(texture_coords), texture_coords, GL_STATIC_DRAW);
	glVertexAttribPointer(TEXTURE_COORD_ATTRIB_POINTER, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);
	glEnableVertexAttribArray(TEXTURE_COORD_ATTRIB_POINTER);

	createBufferObject(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindVertexArray(0);
}