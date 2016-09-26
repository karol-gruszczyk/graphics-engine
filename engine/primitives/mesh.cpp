#include "mesh.hpp"

using engine::Mesh;


Mesh::Mesh(unsigned num_vertices, float* positions, float* normals, float* texture_coords, unsigned num_indices, unsigned* indices)
	: Entity3D({ 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f })
{
	setupRendering(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT);

	glBindVertexArray(m_vao_id);
	createBufferObject(GL_ARRAY_BUFFER, sizeof(float) * 3 * num_vertices, positions, GL_STATIC_DRAW);
	glVertexAttribPointer(POSITION_ATTRIB_POINTER, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
	glEnableVertexAttribArray(POSITION_ATTRIB_POINTER);

	createBufferObject(GL_ARRAY_BUFFER, sizeof(float) * 3 * num_vertices, normals, GL_STATIC_DRAW);
	glVertexAttribPointer(NORMAL_ATTRIB_POINTER, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
	glEnableVertexAttribArray(NORMAL_ATTRIB_POINTER);

	createBufferObject(GL_ARRAY_BUFFER, sizeof(float) * 2 * num_vertices, texture_coords, GL_STATIC_DRAW);
	glVertexAttribPointer(TEXTURE_COORD_ATTRIB_POINTER, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);
	glEnableVertexAttribArray(TEXTURE_COORD_ATTRIB_POINTER);

	createBufferObject(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned) * num_indices, indices, GL_STATIC_DRAW);
	glBindVertexArray(NULL);
}
