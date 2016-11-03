#include "orthographic_camera.hpp"

#include <glm/gtc/matrix_transform.hpp>


using bauasian::OrthographicCamera;

OrthographicCamera::OrthographicCamera(const glm::uvec2& size, const float& near, const float& far)
		: Camera(near, far)
{
	SizeMixin::setSize(size);
	updateProjectionMatrix();
}

void OrthographicCamera::updateProjectionMatrix()
{
	auto bounds = glm::vec2(m_size) / 2.f;
	m_projection_matrix = glm::ortho(-bounds.x, bounds.x, -bounds.y, bounds.y, m_near, m_far);
	m_buffer.setProjectionMatrix(m_projection_matrix);
}
