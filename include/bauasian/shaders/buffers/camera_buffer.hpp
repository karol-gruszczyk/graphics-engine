#ifndef BAUASIAN_SCENE_BUFFER_HPP
#define BAUASIAN_SCENE_BUFFER_HPP

#include "uniform_buffer.hpp"
#include "bauasian/cameras/camera.hpp"


namespace bauasian
{
	class CameraBuffer;
}
class bauasian::CameraBuffer : public UniformBuffer
{
public:
	struct alignas(16) GlslSceneBuffer
	{
		glm::vec3 camera_postion;
		float near;
		float far;
	};

	static CameraBuffer& getInstance();

	void setCamera(const Camera& camera) const;

private:
	CameraBuffer();
};


#endif /* BAUASIAN_SCENE_BUFFER_HPP */
