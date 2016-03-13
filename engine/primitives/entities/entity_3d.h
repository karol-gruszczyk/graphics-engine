#ifndef ENTITY_3D_
#define ENTITY_3D_

#include "entity.h"


namespace engine
{
	class Entity3D;
}

class engine::Entity3D abstract : public Entity
{
public:
	virtual ~Entity3D();

	void setPosition(glm::vec3 position);
	glm::vec3 getPosition();
	void translate(glm::vec3 position);
	void setRotation(glm::vec3 rotation);
	glm::vec3 getRotation();
	void rotate(glm::vec3 rotation);
	void setScale(glm::vec3 scale);
	glm::vec3 getScale();
	void setPivot(glm::vec3 pivot);
	glm::vec3 getPivot();
protected:
	GLuint m_normal_vbo_id;
	bool m_normal_vbo_created;

	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
	glm::vec3 m_pivot;

	void updateTranslationMatrix() override;
	void updateRotationMatrix() override;
	void updateScaleMatrix() override;
	void updatePivotMatrix() override;
};

#endif /* ENTITY_3D_ */
