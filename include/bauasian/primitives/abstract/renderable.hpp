#ifndef BAUASIAN_RENDERABLE_HPP
#define BAUASIAN_RENDERABLE_HPP

#include <vector>

#include <GL/glew.h>


namespace bauasian
{
	class Renderable;
}

class bauasian::Renderable
{
public:
	Renderable(const GLenum& elements_mode, const GLsizei& elements_count, const GLenum& elements_type);
	virtual ~Renderable();

	virtual void render() const;

protected:
	GLuint m_vao_id;
	GLuint m_vbo_ids[2];
	GLenum m_elements_mode, m_elements_type;
	GLsizei m_elements_count;

	void updateVertexBuffer(const GLsizeiptr& size, const void* data,
	                        const std::vector<unsigned>& offsets, const GLenum& draw_type) const;
	void updateIndexBuffer(const GLsizeiptr& size, const void* data, const GLenum& draw_type) const;

};

#endif /* BAUASIAN_RENDERABLE_HPP */
