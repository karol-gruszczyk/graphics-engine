#ifndef RENDERER_3D_H_
#define RENDERER_3D_H_

#include "renderer.h"


namespace engine
{
	class Renderer3D;
}

class engine::Renderer3D : public Renderer
{
public:
	Renderer3D();
	Renderer3D(unsigned context_width, unsigned context_height);

	virtual void setContextWidth(unsigned context_width, unsigned context_height) override;
	void setFieldOfView(GLfloat fov);
	GLfloat getFieldOfView();
private:
	GLfloat m_field_of_view = 45.f;

	virtual void updateProjectionMatrix() override;
	virtual void loadDefaultShader() override;
};

#endif /* RENDERER_3D_H_ */