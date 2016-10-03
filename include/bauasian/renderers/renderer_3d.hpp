#ifndef BAUASIAN_RENDERER_3D_HPP
#define BAUASIAN_RENDERER_3D_HPP

#include "renderer.hpp"
#include "bauasian/context_width_interface.hpp"


namespace bauasian
{
	class Renderer3D;
}

class bauasian::Renderer3D : public Renderer
{
public:
	Renderer3D();

	void setFieldOfView(GLfloat fov);
	GLfloat getFieldOfView() const;
private:
	GLfloat m_field_of_view = 45.f;

	void updateProjectionMatrix();
	virtual void loadShader();
	void updateContextSize() override;
};

#endif /* BAUASIAN_RENDERER_3D_HPP */
