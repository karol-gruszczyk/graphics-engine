#include <iostream>
#include "sphere.hpp"


using bauasian::Sphere;

Sphere::Sphere(const float& radius, const unsigned& num_sides)
		: Entity3D(GL_TRIANGLE_STRIP, (num_sides + 2) * 2 * num_sides, GL_UNSIGNED_INT,
				   num_sides * (num_sides - 1) + 2, num_sides * num_sides),
		  m_radius(radius)
{
	auto num_vertices = getNumVertices();
	Vertex3D* vertices = new Vertex3D[num_vertices];

	vertices[0].position = glm::vec3(0.f, m_radius, 0.f);
	vertices[num_vertices - 1].position = glm::vec3(0.f, -m_radius, 0.f);
	for (unsigned i = 1; i < num_sides; i++)
	{
		double h_angle = glm::pi<float>() * i / num_sides;
		for (unsigned j = 0; j < num_sides; j++)
		{
			double angle = glm::two_pi<float>() * j / num_sides;
			auto& vertex = vertices[(i - 1) * num_sides + 1 + j];
			vertex.position = glm::vec3(glm::sin(angle) * glm::sin(h_angle),
										glm::cos(h_angle),
										glm::cos(angle) * glm::sin(h_angle)) * m_radius;
			vertex.uv = {};
		}
	}
	auto num_indices = getNumElements();
	GLuint* indices = new GLuint[num_indices];
	for (unsigned i = 0; i < num_sides; i++)
	{
		indices[i * 2] = 0;
		indices[i * 2 + 1] = i + 1;
	}
	indices[num_sides * 2] = 0;
	indices[num_sides * 2 + 1] = 1;
	indices[num_sides * 2 + 2] = 0xFFFFFFFF;

	updateVertexBuffer(sizeof(Vertex3D) * num_vertices, vertices, Vertex3D::offsets, GL_STATIC_DRAW);
	updateIndexBuffer(sizeof(GLuint) * num_indices, indices, GL_STATIC_DRAW);

	delete[] vertices;
	delete[] indices;
}

const float& Sphere::getRadius() const
{
	return m_radius;
}

void Sphere::render() const
{
	glEnable(GL_PRIMITIVE_RESTART);
	glPrimitiveRestartIndex(0xFFFFFFFF);
	Entity3D::render();
	glDisable(GL_PRIMITIVE_RESTART);
}
