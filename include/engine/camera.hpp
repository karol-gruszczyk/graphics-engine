#ifndef GRAPHICS_ENGINE_CAMERA_HPP
#define GRAPHICS_ENGINE_CAMERA_HPP

#include <glm/glm.hpp>


namespace engine
{
	class Camera;
}

class engine::Camera final
{
public:
	Camera(const glm::vec3 &position = { 0.f, 0.f, 0.f }, const glm::vec3 &rotation = { 0.f, 0.f, 0.f });

	void translate(const glm::vec3 &position);
	void setPosition(const glm::vec3 &position);
	const glm::vec3 &getPosition() const;
	void rotate(const glm::vec3 &rotation);
	void setRotation(const glm::vec3 &rotation);
	const glm::vec3 &getRotation() const;
	void moveForward(const float &distance);
	void moveRight(const float &distance);
	const glm::vec3 &getForwardVector() const;
	const glm::vec3 &getRightVector() const;
	const glm::mat4 &getViewMatrix() const;
private:
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_forward_vector;
	glm::vec3 m_right_vector;

	glm::mat4 m_view_matrix;

	inline void updateForwardVector();
};

#endif /* GRAPHICS_ENGINE_CAMERA_HPP */
