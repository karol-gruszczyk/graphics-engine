#include "plane.hpp"


using bauasian::Plane;


Plane::Plane(const glm::vec2& size, const unsigned& tile /* = 1 */)
		: m_size(size), m_tile(tile)
{
	m_num_vertices = 4;
	m_num_faces = 2;
	const unsigned floats_per_vertex = 3 + 3 + 2;
	const float& width(size.x), & height(size.y);
	GLfloat vertex_data[] = // position(3) | normal(3) | texture_coordinates(2)
			{
					0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f * m_tile,
					0.f, 0.f, height, 0.f, 1.f, 0.f, 0.f, 0.f,
					width, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f * m_tile, 1.f * m_tile,
					width, 0.f, height, 0.f, 1.f, 0.f, 1.f * m_tile, 0.f,
			};
	GLushort indices[] =
			{
					0, 1, 2, 3
			};

	setupRendering(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT);

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

const glm::vec2& Plane::getSize() const
{
	return m_size;
}

const float& Plane::getTile() const
{
	return m_tile;
}
