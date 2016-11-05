#ifndef BAUASIAN_CAMERA_HPP
#define BAUASIAN_CAMERA_HPP

#include "bauasian/mixins/name_mixin.hpp"
#include "bauasian/uniform_buffers/camera_buffer.hpp"

#include <glm/glm.hpp>


namespace bauasian
{
	class Camera;
}

class bauasian::Camera : public NameMixin
{
public:
	Camera(float near, float far);
	virtual ~Camera();

	void bind() const;

	const glm::vec3& getPosition() const
	{ return m_position; }
	void move(const glm::vec3& position);
	void setPosition(const glm::vec3& position);

	void rotate(float angle, const glm::vec3& axis);
	void roll(float angle);
	void pitch(float angle);
	void yaw(float angle);

	void lookAt(const glm::vec3& position);
	void lookAt(const glm::vec3& eye_position, const glm::vec3& position, const glm::vec3& up);

	const glm::vec3& getDirection() const
	{ return m_direction; }
	const glm::vec3& getUp() const
	{ return m_up; }
	const glm::vec3& getRight() const
	{ return m_right; }

	float getNear() const
	{ return m_near; }
	void setNear(float near);
	float getFar() const
	{ return m_far; }
	void setFar(float far);

	const glm::mat4& getViewMatrix() const
	{ return m_view_matrix; }
	const glm::mat4& getProjectionMatrix() const
	{ return m_projection_matrix; }

protected:
	CameraBuffer m_buffer;

	glm::vec3 m_position;
	float m_near;
	float m_far;

	glm::vec3 m_direction;
	glm::vec3 m_up = glm::vec3(0.f, 1.f, 0.f);
	glm::vec3 m_right;

	glm::mat4 m_view_matrix;
	glm::mat4 m_projection_matrix;

	void setViewMatrix(const glm::mat4& view_matrix);
	virtual void updateProjectionMatrix() = 0;

};

#endif /* BAUASIAN_CAMERA_HPP */
