#include "camera.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/rotate_vector.hpp>


using bauasian::Camera;

Camera::Camera(float near, float far)
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

void Camera::rotate(float angle, const glm::vec3& axis)
{
	m_view_matrix = glm::translate(m_view_matrix, m_position);
	m_view_matrix = glm::rotate(m_view_matrix, -angle, axis);
	m_direction = glm::rotate(m_direction, angle, axis);
	m_right = glm::rotate(m_right, angle, axis);
	m_up = glm::cross(m_right, m_direction);
	setViewMatrix(glm::translate(m_view_matrix, -m_position));
}

void Camera::roll(float angle)
{
	rotate(angle, m_direction);
}

void Camera::pitch(float angle)
{
	rotate(angle, m_right);
}

void Camera::yaw(float angle)
{
	rotate(angle, m_up);
}

void Camera::lookAt(const glm::vec3& position)
{
	m_direction = glm::normalize(position - m_position);
	m_right = glm::cross(m_direction, m_up);
	setViewMatrix(glm::lookAt(m_position, position, m_up));
}

void Camera::lookAt(const glm::vec3& eye_position, const glm::vec3& position, const glm::vec3& up)
{
	m_position = eye_position;
	m_up = up;
	m_direction = glm::normalize(position - m_position);
	m_right = glm::cross(m_direction, m_up);
	setViewMatrix(glm::lookAt(eye_position, position, up));
	m_buffer.setPosition(m_position);
}

void Camera::setNear(float near)
{
	m_near = near;
	updateProjectionMatrix();
	m_buffer.setNear(m_near);
}

void Camera::setFar(float far)
{
	m_far = far;
	updateProjectionMatrix();
	m_buffer.setFar(m_far);
}

void Camera::setViewMatrix(const glm::mat4& view_matrix)
{
	m_view_matrix = view_matrix;
	m_buffer.setViewMatrix(m_view_matrix);
}
