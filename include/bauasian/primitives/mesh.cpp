#include "mesh.hpp"


using bauasian::Mesh;


Mesh::Mesh(unsigned num_vertices, float* vertex_data, unsigned num_indices, unsigned* indices)
{
	m_num_vertices = num_vertices;
	m_num_faces = num_indices / 3;
	setupRendering(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT);

	const unsigned floats_per_vertex = 3 + 3 + 2;
	glBindVertexArray(m_vao_id);
	createBufferObject(GL_ARRAY_BUFFER, sizeof(float) * (3 + 3 + 2) * num_vertices, vertex_data, GL_STATIC_DRAW);
	glVertexAttribPointer(POSITION_ATTRIB_POINTER, 3, GL_FLOAT, GL_FALSE,
	                      floats_per_vertex * sizeof(GLfloat), nullptr);
	glEnableVertexAttribArray(POSITION_ATTRIB_POINTER);

	glVertexAttribPointer(NORMAL_ATTRIB_POINTER, 3, GL_FLOAT, GL_FALSE,
	                      floats_per_vertex * sizeof(GLfloat), reinterpret_cast<void*>(sizeof(GLfloat) * 3));
	glEnableVertexAttribArray(NORMAL_ATTRIB_POINTER);

	glVertexAttribPointer(TEXTURE_COORD_ATTRIB_POINTER, 2, GL_FLOAT, GL_FALSE,
	                      floats_per_vertex * sizeof(GLfloat), reinterpret_cast<void*>(sizeof(GLfloat) * 6));
	glEnableVertexAttribArray(TEXTURE_COORD_ATTRIB_POINTER);

	createBufferObject(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned) * num_indices, indices, GL_STATIC_DRAW);
	glBindVertexArray(0);
}
