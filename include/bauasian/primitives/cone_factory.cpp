#include "cone_factory.hpp"

#include <glm/gtc/constants.hpp>


using bauasian::ConeFactory;

const std::vector<glm::vec3> ConeFactory::getPositions(unsigned num_sides, float radius, float height)
{
	std::vector<glm::vec3> positions(getNumVertices(num_sides));

	positions[0] = glm::vec3(0.f, height, 0.f);
	for (unsigned i = 0; i < num_sides; i++)
	{
		float angle = glm::two_pi<float>() * i / num_sides;
		positions[i + 1] = glm::vec3(glm::sin(angle), 0.f, glm::cos(angle)) * radius;
	}
	positions[positions.size() - 1] = glm::vec3(0.f, 0.f, 0.f);

	return positions;
}

const std::vector<GLuint> ConeFactory::getIndices(unsigned num_sides)
{
	unsigned num_vertices = getNumVertices(num_sides);
	std::vector<GLuint> indices(getNumIndices(num_sides));

	unsigned index = 0;
	indices[index] = 0;
	for (unsigned i = 1; i <= num_sides; i++)
		indices[++index] = i;
	indices[++index] = 1;
	indices[++index] = 0xFFFFFFFF;

	indices[++index] = num_vertices - 1;
	for (unsigned i = num_sides; i >= 1; i--)
		indices[++index] = i;
	indices[++index] = num_sides;

	return indices;
}

unsigned ConeFactory::getNumVertices(unsigned num_sides)
{
	return num_sides + 2;
}

unsigned ConeFactory::getNumIndices(unsigned num_sides)
{
	return num_sides * 2 + 5;
}

unsigned ConeFactory::getNumTriangles(unsigned num_sides)
{
	return 2 * num_sides;
}
