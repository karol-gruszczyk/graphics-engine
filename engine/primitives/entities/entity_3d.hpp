#ifndef ENTITY_3D_
#define ENTITY_3D_

#include "entity.hpp"
#include "../../materials/material.hpp"


namespace engine
{
	class Entity3D;
}

class engine::Entity3D abstract : public Entity
{
public:
	Entity3D(const glm::vec3& position, const glm::vec3& rotation = { 0.f, 0.f, 0.f }, const glm::vec3& scale = { 1.f, 1.f, 1.f }, const glm::vec3& pivot = { 0.f, 0.f, 0.f });
	virtual ~Entity3D();

	void translate(const glm::vec3& position);
	void setPosition(const glm::vec3& position);
	const glm::vec3& getPosition() const;
	void rotate(const glm::vec3& rotation);
	void setRotation(const glm::vec3& rotation);
	const glm::vec3& getRotation() const;
	void setScale(const glm::vec3& scale);
	const glm::vec3& getScale() const;
	void setPivot(const glm::vec3& pivot);
	const glm::vec3& getPivot() const;

	glm::mat3 getNormalMatrix() const;
	void setMaterial(Material* material);
	void render() const override;
protected:
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
	glm::vec3 m_pivot;

	Material* m_material;
};

#endif /* ENTITY_3D_ */
