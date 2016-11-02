#include "perspective_camera.hpp"

#include <glm/gtc/matrix_transform.hpp>


using bauasian::PerspectiveCamera;

PerspectiveCamera::PerspectiveCamera(const float& aspect_ratio, const float& field_of_view, const float& near,
									 const float& far)
		: Camera(near, far), m_aspect_ratio(aspect_ratio), m_field_of_view(field_of_view)
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

void PerspectiveCamera::updateProjectionMatrix()
{
	m_projection_matrix = glm::perspective(m_field_of_view, m_aspect_ratio, m_near, m_far);
	m_buffer.setProjectionMatrix(m_projection_matrix);
}
