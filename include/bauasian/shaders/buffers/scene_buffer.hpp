#ifndef BAUASIAN_SCENE_BUFFER_HPP
#define BAUASIAN_SCENE_BUFFER_HPP

#include "uniform_buffer.hpp"
#include "bauasian/lights/directional_light.hpp"
#include "bauasian/lights/spot_light.hpp"
#include "bauasian/glsl/globals.glsl"


namespace bauasian
{
	class SceneBuffer;
}
class bauasian::SceneBuffer : public UniformBuffer
{
public:
	struct alignas(16) GlslSceneBuffer
	{
		glm::vec3 camera_postion;
	};

	static SceneBuffer& getInstance();

	void setCameraPosition(const glm::vec3& camera_position);

private:
	SceneBuffer();
};


#endif /* BAUASIAN_SCENE_BUFFER_HPP */
