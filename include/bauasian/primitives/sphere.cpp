#include "sphere.hpp"


using bauasian::Sphere;

Sphere::Sphere(const float& radius, const unsigned& num_sides)
		: Entity3D(GL_TRIANGLE_STRIP,
				   ((num_sides - 1) * 2 + 3) * num_sides,
				   GL_UNSIGNED_INT,
				   num_sides * (num_sides - 1) + 2, num_sides * (num_sides - 1) * 2),
		  m_radius(radius)
{
	assert(num_sides >= 3);
	auto num_vertices = getNumVertices();
	Vertex3D* vertices = new Vertex3D[num_vertices];

	unsigned index = 0;
	auto process_vertex = [](Vertex3D& vertex, const glm::vec3& pos) -> void
	{
		vertex.position = pos;
		vertex.normal = glm::normalize(pos);
		vertex.uv = glm::vec2(vertex.position.x, vertex.position.z);
	};
	process_vertex(vertices[index], glm::vec3(0.f, m_radius, 0.f));
	for (unsigned i = 1; i < num_sides; i++)
	{
		double h_angle = glm::pi<float>() * i / num_sides;
		for (unsigned j = 0; j < num_sides; j++)
		{
			double angle = glm::two_pi<float>() * j / num_sides;
			process_vertex(vertices[++index], glm::vec3(glm::sin(angle) * glm::sin(h_angle),
														glm::cos(h_angle),
														glm::cos(angle) * glm::sin(h_angle)) * m_radius);
		}
	}
	process_vertex(vertices[++index], glm::vec3(0.f, -m_radius, 0.f));

	auto num_indices = getNumElements();
	GLuint* indices = new GLuint[num_indices];
	for (unsigned j = 0; j < num_sides; j++)
	{
		index = j * (num_sides * 2 + 1);
		indices[index] = 0;
		GLuint first = j + 1;
		GLuint second = j + 2;
		if (j == num_sides - 1)
			second = 1;
		for (unsigned i = 1; i < num_sides; i++)
		{
			indices[++index] = first;
			indices[++index] = second;
			first += num_sides;
			second += num_sides;
		}
		indices[++index] = num_vertices - 1;
		indices[++index] = 0xFFFFFFFF;
	}

	calculateTangents(vertices, indices, (unsigned) num_indices);
	updateVertexBuffer(sizeof(Vertex3D) * num_vertices, vertices, Vertex3D::offsets, GL_STATIC_DRAW);
	updateIndexBuffer(sizeof(GLuint) * num_indices, indices, GL_STATIC_DRAW);

	delete[] vertices;
	delete[] indices;
}

const float& Sphere::getRadius() const
{
	return m_radius;
}
