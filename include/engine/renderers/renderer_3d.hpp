#ifndef GRAPHICS_ENGINE_RENDERER_3D_HPP
#define GRAPHICS_ENGINE_RENDERER_3D_HPP

#include "renderer.hpp"


namespace engine
{
	class Renderer3D;
}

class engine::Renderer3D : public Renderer
{
public:
	Renderer3D(const unsigned& context_width, const unsigned& context_height);

	virtual void setContextWidth(const unsigned& context_width, const unsigned& context_height) override;
	void setFieldOfView(GLfloat fov);
	GLfloat getFieldOfView() const;
private:
	GLfloat m_field_of_view = 45.f;

	virtual void updateProjectionMatrix() override;
	virtual void loadShader();
};

#endif /* GRAPHICS_ENGINE_RENDERER_3D_HPP */
