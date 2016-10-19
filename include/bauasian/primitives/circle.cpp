#include "circle.hpp"


using bauasian::Circle;

Circle::Circle(const float& radius, const unsigned short& num_sides)
		: Entity2D(GL_TRIANGLE_FAN, num_sides + 2, GL_UNSIGNED_SHORT), m_radius(radius)
{
	assert(num_sides >= 3);
	auto num_vertices = num_sides + 1;
	Vertex2D* vertices = new Vertex2D[num_vertices];

	vertices[0].position = { 0.f, 0.f };
	vertices[0].uv = { 0.5f, 0.5f };
	for (auto i = 1; i < num_vertices; i++)
	{
		auto angle = M_PI * 2.f * i / num_sides;
		vertices[i].position = { glm::sin(angle) * radius, glm::cos(angle) * radius };
		vertices[i].uv = { glm::sin(angle) / 2.f + 0.5f, glm::cos(angle) / 2.f + 0.5f };
	}

	auto num_indices = num_vertices + 1;
	GLushort* indices = new GLushort[num_indices];
	for (unsigned short i = 0; i < num_indices - 1; i++)
		indices[i] = i;
	indices[num_indices - 1] = 1;

	updateVertexBuffer(sizeof(Vertex2D) * num_vertices, vertices, { 4 }, GL_STATIC_DRAW);
	updateIndexBuffer(sizeof(GLushort) * num_indices, indices, GL_STATIC_DRAW);

	delete[] vertices;
	delete[] indices;
}

const float& Circle::getRadius() const
{
	return m_radius;
}