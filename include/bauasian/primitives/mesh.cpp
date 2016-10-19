#include "mesh.hpp"


using bauasian::Mesh;


Mesh::Mesh(unsigned num_vertices, Vertex3D* vertex_data, unsigned num_indices, unsigned* indices)
		: Entity3D(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, num_vertices, num_indices / 3)
{
	updateVertexBuffer(sizeof(Vertex3D) * num_vertices, vertex_data, Entity3D::Vertex3D::offsets, GL_STATIC_DRAW);
	updateIndexBuffer(sizeof(unsigned) * num_indices, indices, GL_STATIC_DRAW);
}
