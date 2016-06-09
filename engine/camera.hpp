#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include <glm/glm.hpp>


namespace engine
{
	class Camera;
}

class engine::Camera final
{
public:
	Camera(glm::vec3 position = { 0.f, 0.f, 0.f }, glm::vec3 rotation = { 0.f, 0.f, 0.f });

	void translate(glm::vec3 position);
	void setPosition(glm::vec3 position);
	glm::vec3 getPosition();
	void rotate(glm::vec3 rotation);
	void setRotation(glm::vec3 rotation);
	glm::vec3 getRotation();
	void moveForward(float distance);
	void moveRight(float distance);
	glm::vec3& getForwardVector();
	glm::vec3& getRightVector();
	glm::mat4& getViewMatrix();
private:
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_forward_vector;
	glm::vec3 m_right_vector;

	glm::mat4 m_view_matrix;

	inline void updateForwardVector();
};

#endif /* CAMERA_HPP_ */
