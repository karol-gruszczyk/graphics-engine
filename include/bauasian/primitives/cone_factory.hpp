#ifndef BAUASIAN_CONE_FACTORY_HPP
#define BAUASIAN_CONE_FACTORY_HPP

#include <vector>

#include <glm/glm.hpp>
#include <GL/glew.h>


namespace bauasian
{
	class ConeFactory;
}

class bauasian::ConeFactory
{
public:
	ConeFactory() = delete;
	ConeFactory(const ConeFactory&) = delete;
	ConeFactory& operator=(const ConeFactory&) = delete;

	static const std::vector<glm::vec3> getPositions(unsigned num_sides, float radius, float height);
	static const std::vector<GLuint> getIndices(unsigned num_sides);
	static unsigned getNumVertices(unsigned num_sides);
	static unsigned getNumIndices(unsigned num_sides);
	static unsigned getNumTriangles(unsigned num_sides);

};


#endif /* BAUASIAN_CONE_FACTORY_HPP */
