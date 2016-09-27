#ifndef GRAPHICS_ENGINE_MESH_HPP
#define GRAPHICS_ENGINE_MESH_HPP

#include "entities/entity_3d.hpp"


namespace engine
{
	class Mesh;
}

class engine::Mesh : public engine::Entity3D
{
public:
	Mesh(unsigned num_vertices, float *vertices, float *normals, float *texture_coords, unsigned num_indices,
	     unsigned *indices);

private:
};

#endif /* GRAPHICS_ENGINE_MESH_HPP */
