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
	PerspectiveCamera(const float& aspect_ratio = 16.f / 9.f, const float& field_of_view = 45.f,
					  const float& near = 0.1f, const float& far = 1000.f);

	const float& getAspectRatio() const;
	void setAspectRatio(const float& aspect_ratio);
	const float& getFieldOfView() const;
	void setFieldOfView(const float& field_of_view);
	const float& getNear() const;
	void setNear(const float& near);
	const float& getFar() const;
	void setFar(const float&  far);

private:
	float m_aspect_ratio;
	float m_field_of_view;
	float m_near;
	float m_far;

	void updateProjectionMatrix() override;

};

#endif /* BAUASIAN_PERSPECTIVE_CAMERA_HPP */
