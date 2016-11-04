#ifndef BAUASIAN_ORTHOGRAPHIC_CAMERA_HPP
#define BAUASIAN_ORTHOGRAPHIC_CAMERA_HPP

#include "camera.hpp"
#include "bauasian/mixins/size_mixin.hpp"


namespace bauasian
{
	class OrthographicCamera;
}

class bauasian::OrthographicCamera : public Camera, public SizeMixin<glm::uvec2>
{
public:
	OrthographicCamera(const glm::uvec2& size, float near = -1000.f, float far = 1000.f);

private:
	void updateProjectionMatrix() override;

};

#endif /* BAUASIAN_ORTHOGRAPHIC_CAMERA_HPP */
