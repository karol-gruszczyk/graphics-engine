#include "scene_buffer.hpp"

#include <glm/gtc/type_ptr.hpp>


using bauasian::SceneBuffer;

SceneBuffer& SceneBuffer::getInstance()
{
	static SceneBuffer instance;
	return instance;
}

SceneBuffer::SceneBuffer()
		: UniformBuffer(sizeof(GlslSceneBuffer), UniformBuffer::SCENE)
{}

void SceneBuffer::setCameraPosition(const glm::vec3& camera_position)
{
	setSubData(0, sizeof(camera_position), glm::value_ptr(camera_position));
}
