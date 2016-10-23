#include "sphere_factory.hpp"

#include <glm/gtc/constants.hpp>


using bauasian::SphereFactory;

const std::vector<glm::vec3> SphereFactory::getPositions(const unsigned& num_sides, const float& radius)
{
	std::vector<glm::vec3> positions(getNumVertices(num_sides));
	unsigned index = 0;
	positions[index] = glm::vec3(0.f, 1.f, 0.f) * radius;
	for (unsigned i = 1; i < num_sides; i++)
	{
		double h_angle = glm::pi<float>() * i / num_sides;
		for (unsigned j = 0; j < num_sides; j++)
		{
			double angle = glm::two_pi<float>() * j / num_sides;
			positions[++index] = glm::vec3(glm::sin(angle) * glm::sin(h_angle),
										   glm::cos(h_angle),
										   glm::cos(angle) * glm::sin(h_angle)) * radius;
		}
	}
	positions[++index] = glm::vec3(0.f, -1.f, 0.f) * radius;
	return positions;
}

const std::vector<GLuint> SphereFactory::getIndices(const unsigned& num_sides)
{
	std::vector<GLuint> indices(getNumIndices(num_sides));
	auto num_vertices = getNumVertices(num_sides);
	for (unsigned j = 0; j < num_sides; j++)
	{
		unsigned index = j * (num_sides * 2 + 1);
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
	return indices;
}

const unsigned SphereFactory::getNumVertices(const unsigned& num_sides)
{
	return num_sides * (num_sides - 1) + 2;
}

const unsigned SphereFactory::getNumIndices(const unsigned& num_sides)
{
	return ((num_sides - 1) * 2 + 3) * num_sides;
}

const unsigned SphereFactory::getNumTriangles(const unsigned& num_sides)
{
	return num_sides * (num_sides - 1) * 2;
}
