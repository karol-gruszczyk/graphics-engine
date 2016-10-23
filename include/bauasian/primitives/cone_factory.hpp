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

	static const std::vector<glm::vec3> getPositions(const unsigned& num_sides, const float& radius,
													 const float& height);
	static const std::vector<GLuint> getIndices(const unsigned& num_sides);
	static const unsigned getNumVertices(const unsigned& num_sides);
	static const unsigned getNumIndices(const unsigned& num_sides);
	static const unsigned getNumTriangles(const unsigned& num_sides);

};


#endif /* BAUASIAN_CONE_FACTORY_HPP */
