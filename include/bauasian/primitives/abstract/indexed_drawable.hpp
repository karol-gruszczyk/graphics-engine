#ifndef BAUASIAN_INDEXED_DRAWABLE_HPP
#define BAUASIAN_INDEXED_DRAWABLE_HPP

#include "drawable.hpp"


namespace bauasian
{
    class IndexedDrawable;
}

class bauasian::IndexedDrawable : public Drawable
{
public:
    IndexedDrawable(GLenum elements_mode, GLsizei elements_count, GLenum elements_type);
    virtual ~IndexedDrawable();

    virtual void render() const override;

protected:
    GLuint m_index_vbo_id;
	GLenum m_elements_type;

    void updateIndexBuffer(GLsizeiptr size, const void* data, GLenum draw_type) const;

};

#endif /* BAUASIAN_INDEXED_DRAWABLE_HPP */
