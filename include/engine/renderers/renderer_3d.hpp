#ifndef GRAPHICS_ENGINE_RENDERER_3D_HPP
#define GRAPHICS_ENGINE_RENDERER_3D_HPP

#include "renderer.hpp"
#include "engine/context_width_interface.hpp"


namespace engine
{
	class Renderer3D;
}

class engine::Renderer3D : public Renderer
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

#endif /* GRAPHICS_ENGINE_RENDERER_3D_HPP */
