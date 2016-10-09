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

void SceneBuffer::setDirectionalLights(const DirectionalLight* dir_lights, const unsigned& count)
{
	setSubData(0, sizeof(DirectionalLight) * count, dir_lights);
}

void SceneBuffer::setPointLights(const PointLight* point_lights, const unsigned int& count)
{
	setSubData(sizeof(DirectionalLight) * MAX_DIR_LIGHTS, sizeof(PointLight) * count, point_lights);
}

void SceneBuffer::setSpotLights(const SpotLight* spot_lights, const unsigned& count)
{
	setSubData(sizeof(DirectionalLight) * MAX_DIR_LIGHTS + sizeof(PointLight) * MAX_POINT_LIGHTS,
	           sizeof(SpotLight) * count, spot_lights);
}

void SceneBuffer::setCameraPosition(const glm::vec3& camera_position)
{
	setSubData(sizeof(DirectionalLight) * MAX_DIR_LIGHTS + sizeof(PointLight) * MAX_POINT_LIGHTS
	           + sizeof(SpotLight) * MAX_SPOT_LIGHTS,
	           sizeof(glm::vec3), glm::value_ptr(camera_position));
}

void SceneBuffer::setNumLights(const unsigned* num_lights)
{
	setSubData(sizeof(DirectionalLight) * MAX_DIR_LIGHTS + sizeof(PointLight) * MAX_POINT_LIGHTS
	           + sizeof(SpotLight) * MAX_SPOT_LIGHTS + sizeof(glm::vec3),
	           sizeof(int) * 3, num_lights);
}
