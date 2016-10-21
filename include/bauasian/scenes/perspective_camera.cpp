#include "perspective_camera.hpp"

#include <glm/gtc/matrix_transform.hpp>


using bauasian::PerspectiveCamera;

PerspectiveCamera::PerspectiveCamera(const float& aspect_ratio, const float& field_of_view, const float& near,
									 const float& far)
		: m_aspect_ratio(aspect_ratio), m_field_of_view(field_of_view), m_near(near), m_far(far)
{
	updateProjectionMatrix();
}

const float& PerspectiveCamera::getAspectRatio() const
{
	return m_aspect_ratio;
}

void PerspectiveCamera::setAspectRatio(const float& aspect_ratio)
{
	m_aspect_ratio = aspect_ratio;
	updateProjectionMatrix();
}

const float& PerspectiveCamera::getFieldOfView() const
{
	return m_field_of_view;
}

void PerspectiveCamera::setFieldOfView(const float& field_of_view)
{
	m_field_of_view = field_of_view;
	updateProjectionMatrix();
}

const float& PerspectiveCamera::getNear() const
{
	return m_near;
}

void PerspectiveCamera::setNear(const float& near)
{
	m_near = near;
	updateProjectionMatrix();
}

const float& PerspectiveCamera::getFar() const
{
	return m_far;
}

void PerspectiveCamera::setFar(const float& far)
{
	m_far = far;
	updateProjectionMatrix();
}

void PerspectiveCamera::updateProjectionMatrix()
{
	m_projection_matrix = glm::perspective(m_field_of_view, m_aspect_ratio, m_near, m_far);
	updateProjectionViewMatrix();
}
