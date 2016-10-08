#include "mesh.hpp"


using bauasian::Mesh;


Mesh::Mesh(unsigned num_vertices, float* vertex_data, unsigned num_indices, unsigned* indices)
		: Entity3D(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, num_vertices, num_indices / 3)
{
	glBindVertexArray(m_vao_id);
	updateVertexBuffer(sizeof(float) * (3 + 3 + 2) * num_vertices, vertex_data, { 3, 3, 2 }, GL_STATIC_DRAW);
	updateIndexBuffer(sizeof(unsigned) * num_indices, indices, GL_STATIC_DRAW);
}
