#ifndef BAUASIAN_BOX_HPP
#define BAUASIAN_BOX_HPP

#include "abstract/entity_3d.hpp"


namespace bauasian
{
	class Box;
}

class bauasian::Box : public Entity3D
{
public:
	Box(const glm::vec3& size);

	const glm::vec3& getSize() const;
	void render() const override;

private:
	glm::vec3 m_size;
};

#endif /* BAUASIAN_BOX_HPP */
