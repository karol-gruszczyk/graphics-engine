#include "sphere_volume.hpp"
#include "sphere_factory.hpp"


using bauasian::SphereVolume;

SphereVolume::SphereVolume(unsigned num_sides)
		: Entity3D(GL_TRIANGLE_STRIP, SphereFactory::getNumIndices(num_sides), GL_UNSIGNED_INT,
				   SphereFactory::getNumVertices(num_sides), SphereFactory::getNumTriangles(num_sides))
{
	auto vertices = SphereFactory::getPositions(num_sides, 1.f);
	auto indices = SphereFactory::getIndices(num_sides);
	updateVertexBuffer(sizeof(glm::vec3) * vertices.size(), vertices.data(), { 3 }, GL_STATIC_DRAW);
	updateIndexBuffer(sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);
}
