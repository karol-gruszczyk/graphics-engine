#ifndef CAMERA_H_
#define CAMERA_H_

#include <glm/glm.hpp>


namespace engine
{
	class Camera;
}

class engine::Camera final
{
public:
	Camera();

	void setPosition(glm::vec3 position);
	glm::vec3 getPosition();
	void translate(glm::vec3 position);
	void moveForward(float distance);
	void moveRight(float distance);
	void setRotation(glm::vec3 rotation);
	glm::vec3 getRotation();
	void rotate(glm::vec3 rotation);
	glm::vec3& getForwardVector();
	glm::vec3& getRightVector();
	glm::mat4& getViewMatrix();
private:
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_forward_vector;
	glm::vec3 m_right_vector;

	glm::mat4 m_translation_matrix;
	glm::mat4 m_rotation_matrix;

	void updateTranslationMatrix();
	void updateRotationMatrix();
};

#endif
