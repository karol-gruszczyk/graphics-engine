#include "camera_buffer.hpp"
#include "bauasian/glsl/bindings.glsl"

#include <glm/gtc/type_ptr.hpp>


struct alignas(16) UniformBlock
{
	glm::mat4 projection_matrix;	// 0
	glm::mat4 view_matrix;			// 64
	glm::vec3 postion;				// 128
	float near;						// 140
	float far;						// 144
};

using bauasian::CameraBuffer;

CameraBuffer::CameraBuffer()
		: UniformBuffer(sizeof(UniformBlock), BUFFER_CAMERA_BINDING)
{}

void CameraBuffer::setProjectionMatrix(const glm::mat4& matrix) const
{
	setSubData(0, sizeof(glm::mat4), glm::value_ptr(matrix));
}
void CameraBuffer::setViewMatrix(const glm::mat4& matrix) const
{
	setSubData(64, sizeof(glm::mat4), glm::value_ptr(matrix));
}

void CameraBuffer::setPosition(const glm::vec3& position) const
{
	setSubData(128, sizeof(glm::vec3), glm::value_ptr(position));
}

void CameraBuffer::setNear(const float& near) const
{
	setSubData(140, sizeof(float), &near);
}

void CameraBuffer::setFar(const float& far) const
{
	setSubData(144, sizeof(float), &far);
}
