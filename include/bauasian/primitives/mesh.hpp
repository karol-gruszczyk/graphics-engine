#ifndef BAUASIAN_MESH_HPP
#define BAUASIAN_MESH_HPP

#include "abstract/entity_3d.hpp"


namespace bauasian
{
	class Mesh;
}

class bauasian::Mesh : public bauasian::Entity3D
{
public:
	Mesh(unsigned num_vertices, float* vertices, unsigned num_indices, unsigned* indices);

private:
};

#endif /* BAUASIAN_MESH_HPP */
