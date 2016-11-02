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

	void setPosition(const glm::vec3& position) const;
	void setNear(const float& near) const;
	void setFar(const float& far) const;

};

#endif /* BAUASIAN_CAMERA_BUFFER_HPP */
