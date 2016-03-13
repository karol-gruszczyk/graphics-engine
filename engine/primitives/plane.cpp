#include "plane.h"

using engine::Plane;

Plane::Plane()
{

}

Plane::Plane(glm::vec2 size, glm::vec3 position /* = { 0.f, 0.f, 0.f } */, glm::vec3 rotation /* = { 0.f, 0.f, 0.f } */, glm::vec3 pivot /* = { 0.f, 0.f, 0.f } */)
{
	initialize(size, position, rotation, pivot);
}

void Plane::initialize(glm::vec2 size, glm::vec3 position /* = { 0.f, 0.f, 0.f } */, glm::vec3 rotation /* = { 0.f, 0.f, 0.f } */, glm::vec3 pivot /* = { 0.f, 0.f, 0.f } */)
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
		m_width, 0.f, m_length,
		m_width, 0.f, 0.f
	};
	GLfloat texture_coords[] =
	{
		0.f, 1.f,
		1.f, 1.f,
		1.f, 0.f,
		0.f, 0.f
	};
	GLfloat normals[] =
	{
		0.f, 1.f, 0.f,
		0.f, 1.f, 0.f,
		0.f, 1.f, 0.f,
		0.f, 1.f, 0.f
	};

	glGenBuffers(1, &m_position_vbo_id);
	m_position_vbo_created = true;

	glGenBuffers(1, &m_texture_coord_vbo_id);
	m_texture_coord_vbo_created = true;

	glGenBuffers(1, &m_normal_vbo_id);
	m_normal_vbo_created = true;

	glGenVertexArrays(1, &m_vao_id);
	m_vao_created = true;

	glBindVertexArray(m_vao_id);
		glBindBuffer(GL_ARRAY_BUFFER, m_position_vbo_id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
		glVertexAttribPointer(POSITION_ATTRIB_POINTER, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
		glEnableVertexAttribArray(POSITION_ATTRIB_POINTER);

		glBindBuffer(GL_ARRAY_BUFFER, m_texture_coord_vbo_id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(texture_coords), texture_coords, GL_STATIC_DRAW);
		glVertexAttribPointer(TEXTURE_COORD_ATTRIB_POINTER, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);
		glEnableVertexAttribArray(TEXTURE_COORD_ATTRIB_POINTER);

		glBindBuffer(GL_ARRAY_BUFFER, m_normal_vbo_id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);
		glVertexAttribPointer(NORMAL_ATTRIB_POINTER, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
		glEnableVertexAttribArray(NORMAL_ATTRIB_POINTER);
	glBindVertexArray(NULL);
}

void Plane::render()
{
	glBindVertexArray(m_vao_id);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glBindVertexArray(NULL);
}
