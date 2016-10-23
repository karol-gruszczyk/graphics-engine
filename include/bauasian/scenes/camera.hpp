#ifndef BAUASIAN_CAMERA_HPP
#define BAUASIAN_CAMERA_HPP

#include "bauasian/interfaces/name_interface.hpp"

#include <glm/glm.hpp>


namespace bauasian
{
	class Camera;
}

class bauasian::Camera : public NameInterface
{
public:
	virtual ~Camera();

	const glm::vec3& getPosition() const;
	void move(const glm::vec3& position);
	void setPosition(const glm::vec3& position);

	void rotate(const float& angle, const glm::vec3& axis);
	void roll(const float& angle);
	void pitch(const float& angle);
	void yaw(const float& angle);

	void lookAt(const glm::vec3& position);
	void lookAt(const glm::vec3& eye_position, const glm::vec3& position, const glm::vec3& up);

	const glm::vec3& getDirection() const;
	const glm::vec3& getUp() const;
	const glm::vec3& getRight() const;

	const glm::mat4& getViewMatrix() const;
	const glm::mat4& getProjectionMatrix() const;
	const glm::mat4& getProjectionViewMatrix() const;

protected:
	glm::vec3 m_position;

	glm::vec3 m_direction_vector;
	glm::vec3 m_up_vector = glm::vec3(0.f, 1.f, 0.f);
	glm::vec3 m_right_vector;

	glm::mat4 m_view_matrix;
	glm::mat4 m_projection_matrix;
	glm::mat4 m_projection_view_matrix;

	void setViewMatrix(const glm::mat4& view_matrix);
	void updateProjectionViewMatrix();
	virtual void updateProjectionMatrix() = 0;

};

#endif /* BAUASIAN_CAMERA_HPP */
