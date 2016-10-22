#include "orthographic_camera.hpp"

#include <glm/gtc/matrix_transform.hpp>


using bauasian::OrthographicCamera;

OrthographicCamera::OrthographicCamera(const glm::uvec2& size)
		: SizeInterface(size)
{
	setSize(size);
}

void OrthographicCamera::setSize(const glm::uvec2& size)
{
	SizeInterface::setSize(size);
}

void OrthographicCamera::updateProjectionMatrix()
{
	m_projection_matrix = glm::ortho(-1.f, (float) m_size.x, (float) m_size.y, -1.f);
	updateProjectionViewMatrix();
}
