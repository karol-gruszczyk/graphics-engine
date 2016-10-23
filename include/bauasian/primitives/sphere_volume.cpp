#include "sphere_volume.hpp"
#include "sphere_factory.hpp"


using bauasian::SphereVolume;

SphereVolume::SphereVolume()
		: Entity3D(GL_TRIANGLE_STRIP, SphereFactory::getNumIndices(18), GL_UNSIGNED_INT,
				   SphereFactory::getNumVertices(18), SphereFactory::getNumTriangles(18))
{
	auto vertices = SphereFactory::getPositions(18, 1.f);
	auto indices = SphereFactory::getIndices(18);
	updateVertexBuffer(sizeof(glm::vec3) * vertices.size(), vertices.data(), { 3 }, GL_STATIC_DRAW);
	updateIndexBuffer(sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);
}
