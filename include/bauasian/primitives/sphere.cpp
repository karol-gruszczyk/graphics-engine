#include "sphere.hpp"
#include "sphere_factory.hpp"


using bauasian::Sphere;

Sphere::Sphere(float radius, unsigned num_sides)
		: Entity3D(GL_TRIANGLE_STRIP, SphereFactory::getNumIndices(num_sides), GL_UNSIGNED_INT,
				   SphereFactory::getNumVertices(num_sides), SphereFactory::getNumTriangles(num_sides)),
		  m_radius(radius)
{
	assert(num_sides >= 3);
	auto num_vertices = getNumVertices();
	auto positions = SphereFactory::getPositions(num_sides, radius);
	Vertex3D* vertices = new Vertex3D[num_vertices];

	auto process_vertex = [](Vertex3D& vertex, const glm::vec3& pos) -> void
	{
		vertex.position = pos;
		vertex.normal = glm::normalize(pos);
		vertex.uv = glm::vec2((vertex.normal.x * vertex.normal.z) / 2.f + 0.5f, vertex.normal.y / 2.f + 0.5f);
	};

	for (unsigned i = 0; i < num_vertices; i++)
		process_vertex(vertices[i], positions[i]);

	auto num_indices = getNumElements();
	auto indices = SphereFactory::getIndices(num_sides);

	calculateTangents(vertices, indices.data(), (unsigned) num_indices);
	updateVertexBuffer(sizeof(Vertex3D) * num_vertices, vertices, Vertex3D::offsets, GL_STATIC_DRAW);
	updateIndexBuffer(sizeof(GLuint) * num_indices, indices.data(), GL_STATIC_DRAW);

	delete[] vertices;
}

float Sphere::getRadius() const
{
	return m_radius;
}
