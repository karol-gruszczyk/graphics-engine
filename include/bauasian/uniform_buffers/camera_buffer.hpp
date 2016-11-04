#ifndef BAUASIAN_CAMERA_BUFFER_HPP
#define BAUASIAN_CAMERA_BUFFER_HPP

#include "uniform_buffer.hpp"


namespace bauasian
{
	class CameraBuffer;
}

class bauasian::CameraBuffer : protected UniformBuffer
{
public:
	CameraBuffer();

	using UniformBuffer::bind;

	void setProjectionMatrix(const glm::mat4& matrix) const;
	void setViewMatrix(const glm::mat4& matrix) const;
	void setPosition(const glm::vec3& position) const;
	void setNear(float near) const;
	void setFar(float far) const;

};

#endif /* BAUASIAN_CAMERA_BUFFER_HPP */
