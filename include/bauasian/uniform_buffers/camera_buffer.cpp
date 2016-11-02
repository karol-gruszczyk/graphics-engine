#include "camera_buffer.hpp"
#include "bauasian/glsl/bindings.glsl"

#include <glm/gtc/type_ptr.hpp>


struct alignas(16) UniformBlock
{
	glm::vec3 camera_postion;		// 0
	float near;						// 12
	float far;						// 16
};

using bauasian::CameraBuffer;

CameraBuffer::CameraBuffer()
		: UniformBuffer(sizeof(UniformBlock), BUFFER_CAMERA_BINDING)
{}

void CameraBuffer::setPosition(const glm::vec3& position) const
{
	setSubData(0, sizeof(glm::vec3), glm::value_ptr(position));
}

void CameraBuffer::setNear(const float& near) const
{
	setSubData(12, sizeof(float), &near);
}

void CameraBuffer::setFar(const float& far) const
{
	setSubData(16, sizeof(float), &far);
}
