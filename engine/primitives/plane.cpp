#include "plane.h"

#define ELEMENTS_BUFFER_LENGTH 4

using engine::Plane;

Plane::Plane()
{}

Plane::Plane(glm::vec2 size, glm::vec3 position /* = { 0.f, 0.f, 0.f } */, unsigned tile /* = 1 */, glm::vec3 rotation /* = { 0.f, 0.f, 0.f } */, glm::vec3 pivot /* = { 0.f, 0.f, 0.f } */)
{
	initialize(size, position, tile, rotation, pivot);
}

void Plane::initialize(glm::vec2 size, glm::vec3 position /* = { 0.f, 0.f, 0.f } */, unsigned tile /* = 1 */, glm::vec3 rotation /* = { 0.f, 0.f, 0.f } */, glm::vec3 pivot /* = { 0.f, 0.f, 0.f } */)
{
	m_width = size.x;
	m_length = size.y;
	m_position = position;
	m_rotation = rotation;
	m_pivot = pivot;
	updateTranslationMatrix();

	GLfloat positions[] =
	{
		0.f, 0.f, 0.f,
		0.f, 0.f, m_length,
		m_width, 0.f, 0.f,
		m_width, 0.f, m_length,
	};
	GLfloat texture_coords[] =
	{
		0.f, 1.f * tile,
		0.f, 0.f,
		1.f * tile, 1.f * tile,
		1.f * tile, 0.f
	};
	GLfloat normals[] =
	{
		0.f, 1.f, 0.f,
		0.f, 1.f, 0.f,
		0.f, 1.f, 0.f,
		0.f, 1.f, 0.f
	};
	GLushort indices[] =
	{
		0, 1, 2, 3
	};

	Entity3D::initBuffers();

	static_assert(2 * sizeof(GLfloat) % 4 == 0 || 3 * sizeof(GLfloat) == 0, "Buffer data should be aligned in 4 byte blocks");

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
	glBindVertexArray(NULL);
}

void Plane::render()
{
	glBindVertexArray(m_vao_id);
	glDrawElements(GL_TRIANGLE_STRIP, ELEMENTS_BUFFER_LENGTH, GL_UNSIGNED_SHORT, nullptr);
	glBindVertexArray(NULL);
}
