#ifndef RENDERER_3D_HPP_
#define RENDERER_3D_HPP_

#include "renderer.hpp"


namespace engine
{
	class Renderer3D;
}

class engine::Renderer3D : public Renderer
{
public:
	Renderer3D(unsigned context_width, unsigned context_height);

	virtual void setContextWidth(unsigned context_width, unsigned context_height) override;
	void setFieldOfView(GLfloat fov);
	GLfloat getFieldOfView();
private:
	GLfloat m_field_of_view = 45.f;

	virtual void updateProjectionMatrix() override;
	virtual void loadShader();
};

#endif /* RENDERER_3D_HPP_ */
