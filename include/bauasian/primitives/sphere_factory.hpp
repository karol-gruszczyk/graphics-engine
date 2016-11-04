#ifndef BAUASIAN_PRIMITIVE_FACTORY_HPP
#define BAUASIAN_PRIMITIVE_FACTORY_HPP

#include <vector>

#include <glm/glm.hpp>
#include <GL/glew.h>


namespace bauasian
{
	class SphereFactory;
}

class bauasian::SphereFactory
{
public:
	SphereFactory() = delete;
	SphereFactory(const SphereFactory&) = delete;
	SphereFactory& operator=(const SphereFactory&) = delete;

	static const std::vector<glm::vec3> getPositions(unsigned num_sides, float radius);
	static const std::vector<GLuint> getIndices(unsigned num_sides);
	static unsigned getNumVertices(unsigned num_sides);
	static unsigned getNumIndices(unsigned num_sides);
	static unsigned getNumTriangles(unsigned num_sides);

};

#endif /* BAUASIAN_PRIMITIVE_FACTORY_HPP */
