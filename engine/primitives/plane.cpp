#include "plane.hpp"

using engine::Plane;


Plane::Plane(glm::vec2 size, glm::vec3 position /* = { 0.f, 0.f, 0.f } */, unsigned tile /* = 1 */, 
	glm::vec3 rotation /* = { 0.f, 0.f, 0.f } */, glm::vec3 scale /* = { 1.f, 1.f, 1.f } */, glm::vec3 pivot /* = { 0.f, 0.f, 0.f } */)
	: Entity3D(position, rotation, scale, pivot),
	m_width(size.x), m_length(size.y)
{
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

	setupRendering(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT);

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
