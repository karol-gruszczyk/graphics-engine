#ifndef BAUASIAN_PERSPECTIVE_CAMERA_HPP
#define BAUASIAN_PERSPECTIVE_CAMERA_HPP

#include "camera.hpp"


namespace bauasian
{
	class PerspectiveCamera;
}

class bauasian::PerspectiveCamera : public Camera
{
public:
	PerspectiveCamera(float aspect_ratio = 16.f / 9.f, float field_of_view = 45.f, float near = 0.1f,
					  float far = 1000.f);

	float getAspectRatio() const;
	void setAspectRatio(float aspect_ratio);
	float getFieldOfView() const;
	void setFieldOfView(float field_of_view);

private:
	float m_aspect_ratio;
	float m_field_of_view;

	void updateProjectionMatrix() override;

};

#endif /* BAUASIAN_PERSPECTIVE_CAMERA_HPP */
