#include "camera_buffer.hpp"

#include <glm/gtc/type_ptr.hpp>


using bauasian::CameraBuffer;

CameraBuffer& CameraBuffer::getInstance()
{
	static CameraBuffer instance;
	return instance;
}

CameraBuffer::CameraBuffer()
		: UniformBuffer(sizeof(GlslSceneBuffer), UniformBuffer::SCENE)
{}

void CameraBuffer::setCamera(const Camera& camera) const
{
	setSubData(0, sizeof(glm::vec3), glm::value_ptr(camera.getPosition()));
	setSubData(sizeof(glm::vec3), sizeof(float), &camera.getNear());
	setSubData(sizeof(glm::vec3) + sizeof(float), sizeof(float), &camera.getFar());
}
