#include "entity_3d.hpp"
#include "bauasian/uniform_buffers/matrices_buffer.hpp"

#include <iostream>

#include <glm/gtx/norm.hpp>


using bauasian::Entity3D;
using bauasian::Material;

const std::vector<unsigned> Entity3D::Vertex3D::offsets = { 3, 3, 2, 3, 3 };

Entity3D::Entity3D(const GLenum& elements_mode, const GLsizei& elements_count, const GLenum& elements_type,
				   const unsigned& num_vertices, const unsigned& num_faces)
		: IndexedDrawable(elements_mode, elements_count, elements_type), DrawableStats(num_vertices, num_faces)
{
}

void Entity3D::setMaterial(std::shared_ptr<Material> material)
{
	m_material = material;
}

void Entity3D::render() const
{
	MatricesBuffer::getInstance().setModelMatrix(getModelMatrix());
	MatricesBuffer::getInstance().setNormalMatrix(getNormalMatrix());
	if (m_material)
	{
		m_material->bind();
		IndexedDrawable::render();
	}
	else
		IndexedDrawable::render();
}

void Entity3D::calculateTangents(Entity3D::Vertex3D* vertices, const unsigned* indices, const unsigned& num_indices)
{
	unsigned i = 2;
	while (i < num_indices)
	{
		auto& v1 = vertices[indices[i - 2]];
		auto& v2 = vertices[indices[i - 1]];
		auto& v3 = vertices[indices[i]];

		glm::vec3 edge1 = v2.position - v1.position;
		glm::vec3 edge2 = v3.position - v1.position;
		glm::vec2 deltaUV1 = v2.uv - v1.uv;
		glm::vec2 deltaUV2 = v3.uv - v1.uv;


		GLfloat f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

		glm::vec3 tangent;
		tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
		tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
		tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
		tangent = glm::normalize(tangent);

		v1.tangent = tangent;
		v1.bi_tangent = glm::normalize(glm::cross(v1.normal, tangent));

		v2.tangent = tangent;
		v2.bi_tangent = glm::normalize(glm::cross(v2.normal, tangent));

		v3.tangent = tangent;
		v3.bi_tangent = glm::normalize(glm::cross(v3.normal, tangent));

		if (indices[++i] == 0xFFFFFFFF)
			i += 3;
	}
}

void Entity3D::calculateTangents(Vertex3D* vertices, const unsigned short* indices, const unsigned& num_indices)
{
	unsigned* casted_indices = new unsigned[num_indices];
	for (unsigned i = 0; i < num_indices; i++)
		casted_indices[i] = indices[i] == 0xFFFF ? 0xFFFFFFFF : indices[i];
	calculateTangents(vertices, casted_indices, num_indices);
	delete[] casted_indices;
}
