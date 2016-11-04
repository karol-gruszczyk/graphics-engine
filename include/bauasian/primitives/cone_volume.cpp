#include "cone_volume.hpp"
#include "cone_factory.hpp"


using bauasian::ConeVolume;

ConeVolume::ConeVolume(unsigned num_sides)
		: Entity3D(GL_TRIANGLE_FAN, ConeFactory::getNumIndices(num_sides), GL_UNSIGNED_INT,
				   ConeFactory::getNumVertices(num_sides), ConeFactory::getNumTriangles(num_sides))
{
	auto positions = ConeFactory::getPositions(num_sides, 1.f, 1.f);
	for (auto& position : positions)
		position.y -= 1.f;
	auto indices = ConeFactory::getIndices(num_sides);

	updateVertexBuffer(sizeof(glm::vec3) * positions.size(), positions.data(), { 3 }, GL_STATIC_DRAW);
	updateIndexBuffer(sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);
}
