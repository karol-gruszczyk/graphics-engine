#ifndef BAUASIAN_ORTHOGRAPHIC_CAMERA_HPP
#define BAUASIAN_ORTHOGRAPHIC_CAMERA_HPP

#include "camera.hpp"
#include "bauasian/interfaces/size_interface.hpp"


namespace bauasian
{
	class OrthographicCamera;
}

class bauasian::OrthographicCamera : public Camera, public SizeInterface
{
public:
	OrthographicCamera(const glm::uvec2& size);

	void setSize(const glm::uvec2& size) override;

private:
	void updateProjectionMatrix() override;

};

#endif /* BAUASIAN_ORTHOGRAPHIC_CAMERA_HPP */
