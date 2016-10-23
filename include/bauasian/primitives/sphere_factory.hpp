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

	static const std::vector<glm::vec3> getPositions(const unsigned& num_sides, const float& radius);
	static const std::vector<GLuint> getIndices(const unsigned& num_sides);
	static const unsigned getNumVertices(const unsigned& num_sides);
	static const unsigned getNumIndices(const unsigned& num_sides);
	static const unsigned getNumTriangles(const unsigned& num_sides);

};

#endif /* BAUASIAN_PRIMITIVE_FACTORY_HPP */
