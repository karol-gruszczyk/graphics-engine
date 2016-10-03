#ifndef BAUASIAN_RENDERER_3D_HPP
#define BAUASIAN_RENDERER_3D_HPP

#include "renderer.hpp"
#include "scene_3d.hpp"
#include "frame_buffer.hpp"
#include "bauasian/context_width_interface.hpp"


namespace bauasian
{
	class Renderer3D;
}

class bauasian::Renderer3D : public Renderer
{
public:
	Renderer3D();
	~Renderer3D();

	void setFieldOfView(GLfloat fov);
	GLfloat getFieldOfView() const;
	void render(const Scene3D* scene) const;
private:
	GLfloat m_field_of_view = 45.f;
	FrameBuffer* m_frame_buffer;

	void updateProjectionMatrix();
	virtual void loadShader();
	void updateContextSize() override;
};

#endif /* BAUASIAN_RENDERER_3D_HPP */
