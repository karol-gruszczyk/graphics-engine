#ifndef BAUASIAN_SCENE_BUFFER_HPP
#define BAUASIAN_SCENE_BUFFER_HPP

#include "uniform_buffer.hpp"
#include "bauasian/lights/directional_light.hpp"
#include "bauasian/lights/spot_light.hpp"
#include "bauasian/glsl/3d/globals.glsl"


namespace bauasian
{
	class SceneBuffer;
}
class bauasian::SceneBuffer : public UniformBuffer
{
public:
	struct alignas(16) GlslSceneBuffer
	{
		DirectionalLight directional_lights[MAX_DIR_LIGHTS];
		PointLight point_lights[MAX_POINT_LIGHTS];
		SpotLight spot_lights[MAX_SPOT_LIGHTS];
		glm::vec3 camera_postion;
		int num_lights[3];
	};

	static SceneBuffer& getInstance();

	void setDirectionalLights(const DirectionalLight* dir_lights, const unsigned& count);
	void setPointLights(const PointLight* point_lights, const unsigned& count);
	void setSpotLights(const SpotLight* spot_lights, const unsigned& count);
	void setCameraPosition(const glm::vec3& camera_position);
	void setNumLights(const unsigned* num_lights);

private:
	SceneBuffer();
};


#endif /* BAUASIAN_SCENE_BUFFER_HPP */
