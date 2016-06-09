#include "camera.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

using engine::Camera;


Camera::Camera(glm::vec3 position /* = { 0.f,0.f,0.f } */, glm::vec3 rotation /* = { 0.f, 0.f, 0.f } */)
{
	setPosition(position);
	setRotation(rotation);
}

void Camera::translate(glm::vec3 position)
{
	m_view_matrix = glm::translate(m_view_matrix, -position);
	m_position += position;
}

void Camera::setPosition(glm::vec3 position)
{
	translate(position - m_position);
}

glm::vec3 Camera::getPosition()
{
	return m_position;
}

void Camera::rotate(glm::vec3 rotation)
{
	m_view_matrix = glm::translate(m_view_matrix, m_position);
	m_view_matrix = glm::rotate(m_view_matrix, -m_rotation.y, { 0.f, 1.f, 0.f });
	m_view_matrix = glm::rotate(m_view_matrix, rotation.z, { 0.f, 0.f, 1.f });
	m_view_matrix = glm::rotate(m_view_matrix, -rotation.x, { 1.f, 0.f, 0.f });
	m_view_matrix = glm::rotate(m_view_matrix, m_rotation.y + rotation.y, { 0.f, 1.f, 0.f });
	m_view_matrix = glm::translate(m_view_matrix, -m_position);

	updateForwardVector();
	m_rotation += rotation;
}

void Camera::setRotation(glm::vec3 rotation)
{
	rotate(rotation - m_rotation);
}

glm::vec3 Camera::getRotation()
{
	return m_rotation;
}

void Camera::moveForward(float distance)
{
	translate(distance * getForwardVector());
}

void Camera::moveRight(float distance)
{
	translate(distance * getRightVector());
}

glm::vec3& Camera::getForwardVector()
{
	return m_forward_vector;
}

glm::vec3& Camera::getRightVector()
{
	return m_right_vector;
}

glm::mat4& Camera::getViewMatrix()
{
	return m_view_matrix;
}

inline void Camera::updateForwardVector()
{
	m_forward_vector = glm::vec3(
		cos(m_rotation.x) * glm::sin(m_rotation.y),
		sin(m_rotation.x),
		-cos(m_rotation.x) * glm::cos(m_rotation.y));
	m_right_vector = glm::vec3(
		glm::cos(m_rotation.y),
		0.f,
		glm::sin(m_rotation.y));
}
