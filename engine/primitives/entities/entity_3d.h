#ifndef ENTITY_3D_
#define ENTITY_3D_

#include "entity.h"
#include "../../materials/material.h"


namespace engine
{
	class Entity3D;
}

class engine::Entity3D abstract : public Entity
{
public:
	Entity3D(glm::vec3 position, glm::vec3 rotation = { 0.f, 0.f, 0.f }, glm::vec3 scale = { 1.f, 1.f, 1.f }, glm::vec3 pivot = { 0.f, 0.f, 0.f });
	virtual ~Entity3D();

	void translate(glm::vec3 position);
	void setPosition(glm::vec3 position);
	void rotate(glm::vec3 rotation);
	glm::vec3 getPosition();
	void setRotation(glm::vec3 rotation);
	glm::vec3 getRotation();
	void setScale(glm::vec3 scale);
	glm::vec3 getScale();
	void setPivot(glm::vec3 pivot);
	glm::vec3 getPivot();

	glm::mat3 getNormalMatrix();
	void setMaterial(Material* material);
	void render() override;
protected:
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
	glm::vec3 m_pivot;

	Material* m_material;
};

#endif /* ENTITY_3D_ */
