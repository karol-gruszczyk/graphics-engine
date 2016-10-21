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

	void translate(const glm::vec3& position);
	void setPosition(const glm::vec3& position);
	const glm::vec3& getPosition() const;
	void rotate(const glm::vec3& rotation);
	void setRotation(const glm::vec3& rotation);
	const glm::vec3& getRotation() const;
	void moveForward(const float& distance);
	void moveRight(const float& distance);
	const glm::vec3& getForwardVector() const;
	const glm::vec3& getRightVector() const;
	const glm::mat4& getViewMatrix() const;
	void setViewMatrix(const glm::mat4& view_matrix);
	const glm::mat4& getProjectionMatrix() const;
	const glm::mat4& getProjectionViewMatrix() const;

protected:
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_forward_vector;
	glm::vec3 m_right_vector;

	glm::mat4 m_projection_matrix;
	glm::mat4 m_view_matrix;
	glm::mat4 m_projection_view_matrix;

	inline void updateForwardVector();
	void updateProjectionViewMatrix();
	virtual void updateProjectionMatrix() = 0;

};

#endif /* BAUASIAN_CAMERA_HPP */
