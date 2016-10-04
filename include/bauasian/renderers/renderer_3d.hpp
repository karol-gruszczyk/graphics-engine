#ifndef BAUASIAN_RENDERER_3D_HPP
#define BAUASIAN_RENDERER_3D_HPP

#include "renderer.hpp"
#include "scene_3d.hpp"
#include "bauasian/renderers/post_processors/post_processor.hpp"
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

	const GLfloat& getFieldOfView() const;
	void setFieldOfView(GLfloat fov);
	const GLfloat& getZNear() const;
	void setZNear(GLfloat z_near);
	const GLfloat& getZFar() const;
	void setZFar(GLfloat z_far);
	void addFilter(PostProcessor* filter);
	void render(const Scene3D* scene) const;
private:
	GLfloat m_field_of_view = 45.f;
	GLfloat m_z_near = 0.1f;
	GLfloat m_z_far = 1000.f;
	std::list<PostProcessor*> m_filters;

	void updateProjectionMatrix();
	virtual void loadShader();
	void updateContextSize() override;
};

#endif /* BAUASIAN_RENDERER_3D_HPP */
