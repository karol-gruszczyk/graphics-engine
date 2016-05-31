#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

using engine::Camera;


Camera::Camera(glm::vec3 position /* = { 0.f,0.f,0.f } */, glm::vec3 rotation /* = { 0.f, 0.f, 0.f } */)
	: m_position(position), m_rotation(rotation)
{}

void Camera::setPosition(glm::vec3 position)
{
	m_position = position;
	updateTranslationMatrix();
}

glm::vec3 Camera::getPosition()
{
	return m_position;
}

void Camera::translate(glm::vec3 position)
{
	setPosition(m_position + position);
}

void Camera::moveForward(float distance)
{
	translate(distance * getForwardVector());
}

void Camera::moveRight(float distance)
{
	translate(distance * getRightVector());
}

void Camera::setRotation(glm::vec3 rotation)
{
	m_rotation = rotation;
	if (m_rotation.x > glm::two_pi<float>())
		m_rotation.x -= glm::two_pi<float>();
	if (m_rotation.x < 0.f)
		m_rotation.x += glm::two_pi<float>();

	if (m_rotation.y > glm::two_pi<float>())
		m_rotation.y -= glm::two_pi<float>();
	if (m_rotation.y < 0.f)
		m_rotation.y += glm::two_pi<float>();

	auto pitch = m_rotation.x, yaw = m_rotation.y;
	m_forward_vector = glm::vec3(
		cos(pitch) * glm::sin(yaw),
		sin(pitch),
		-cos(pitch) * glm::cos(yaw));
	m_right_vector = glm::vec3(
		glm::cos(yaw),
		0.f,
		glm::sin(yaw));
}

glm::vec3 Camera::getRotation()
{
	return m_rotation;
}

void Camera::rotate(glm::vec3 rotation)
{
	setRotation(m_rotation + rotation);
	updateRotationMatrix();
}

void Camera::updateTranslationMatrix()
{
	m_translation_matrix = glm::translate(m_rotation_matrix, -m_position);
}

void Camera::updateRotationMatrix()
{
	auto x_rot = glm::rotate(glm::mat4(), -m_rotation.x, { 1.f, 0.f, 0.f });
	auto y_rot = glm::rotate(x_rot, m_rotation.y, { 0.f, 1.f, 0.f });
	m_rotation_matrix = glm::rotate(y_rot, -m_rotation.z, { 0.f, 0.f, 1.f });
	updateTranslationMatrix();
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
	return m_translation_matrix;
}
