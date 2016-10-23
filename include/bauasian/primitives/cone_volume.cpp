#include "cone_volume.hpp"
#include "cone_factory.hpp"


using bauasian::ConeVolume;

ConeVolume::ConeVolume()
		: Entity3D(GL_TRIANGLE_FAN, ConeFactory::getNumIndices(18), GL_UNSIGNED_INT,
				   ConeFactory::getNumVertices(18), ConeFactory::getNumTriangles(18))
{
	auto positions = ConeFactory::getPositions(18, 1.f, 1.f);
	auto indices = ConeFactory::getIndices(18);

	updateVertexBuffer(sizeof(glm::vec3) * positions.size(), positions.data(), { 3 }, GL_STATIC_DRAW);
	updateIndexBuffer(sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);
}
