#include "camera.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/rotate_vector.hpp>


using bauasian::Camera;

Camera::Camera(const float& near, const float& far)
		: m_near(near), m_far(far)
{
	m_buffer.setNear(m_near);
	m_buffer.setFar(m_far);
}

Camera::~Camera()
{}

void Camera::bind() const
{
	m_buffer.bind();
}

const glm::vec3& Camera::getPosition() const
{
	return m_position;
}

void Camera::move(const glm::vec3& position)
{
	setViewMatrix(glm::translate(m_view_matrix, -position));
	m_position += position;
	m_buffer.setPosition(m_position);
}

void Camera::setPosition(const glm::vec3& position)
{
	move(position - m_position);
}

void Camera::rotate(const float& angle, const glm::vec3& axis)
{
	m_view_matrix = glm::translate(m_view_matrix, m_position);
	m_view_matrix = glm::rotate(m_view_matrix, -angle, axis);
	m_direction_vector = glm::rotate(m_direction_vector, angle, axis);
	m_right_vector = glm::rotate(m_right_vector, angle, axis);
	m_up_vector = glm::cross(m_right_vector, m_direction_vector);
	setViewMatrix(glm::translate(m_view_matrix, -m_position));
}

void Camera::roll(const float& angle)
{
	rotate(angle, m_direction_vector);
}

void Camera::pitch(const float& angle)
{
	rotate(angle, m_right_vector);
}

void Camera::yaw(const float& angle)
{
	rotate(angle, m_up_vector);
}

void Camera::lookAt(const glm::vec3& position)
{
	m_direction_vector = glm::normalize(position - m_position);
	m_right_vector = glm::cross(m_direction_vector, m_up_vector);
	setViewMatrix(glm::lookAt(m_position, position, m_up_vector));
}

void Camera::lookAt(const glm::vec3& eye_position, const glm::vec3& position, const glm::vec3& up)
{
	m_position = eye_position;
	m_up_vector = up;
	m_direction_vector = glm::normalize(position - m_position);
	m_right_vector = glm::cross(m_direction_vector, m_up_vector);
	setViewMatrix(glm::lookAt(eye_position, position, up));
	m_buffer.setPosition(m_position);
}

const glm::vec3& Camera::getDirection() const
{
	return m_direction_vector;
}

const glm::vec3& Camera::getUp() const
{
	return m_up_vector;
}

const glm::vec3& Camera::getRight() const
{
	return m_right_vector;
}

const float& Camera::getNear() const
{
	return m_near;
}

void Camera::setNear(const float& near)
{
	m_near = near;
	updateProjectionMatrix();
	m_buffer.setNear(m_near);
}

const float& Camera::getFar() const
{
	return m_far;
}

void Camera::setFar(const float& far)
{
	m_far = far;
	updateProjectionMatrix();
	m_buffer.setFar(m_far);
}

const glm::mat4& Camera::getViewMatrix() const
{
	return m_view_matrix;
}

const glm::mat4& Camera::getProjectionMatrix() const
{
	return m_projection_matrix;
}

void Camera::setViewMatrix(const glm::mat4& view_matrix)
{
	m_view_matrix = view_matrix;
	m_buffer.setViewMatrix(m_view_matrix);
}
