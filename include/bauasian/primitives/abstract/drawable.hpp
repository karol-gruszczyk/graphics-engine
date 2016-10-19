#ifndef BAUASIAN_DRAWABLE_HPP
#define BAUASIAN_DRAWABLE_HPP

#include <vector>

#include <GL/glew.h>


namespace bauasian
{
	class Drawable;
}

class bauasian::Drawable
{
public:
	Drawable(const GLenum& elements_mode, const GLsizei& elements_count);
	virtual ~Drawable();

	const GLsizei& getNumElements() const;
	virtual void render() const;

protected:
	GLuint m_vao_id;
    GLuint m_vertex_vbo_id;
	GLenum m_elements_mode;
	GLsizei m_elements_count;

	void updateVertexBuffer(const GLsizeiptr& size, const void* data,
	                        const std::vector<unsigned>& offsets, const GLenum& draw_type) const;

};

#endif /* BAUASIAN_DRAWABLE_HPP */
