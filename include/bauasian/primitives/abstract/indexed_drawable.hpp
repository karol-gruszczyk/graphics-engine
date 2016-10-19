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
    IndexedDrawable(const GLenum& elements_mode, const GLsizei& elements_count, const GLenum& elements_type);
    virtual ~IndexedDrawable();

    virtual void render() const override;

protected:
    GLuint m_index_vbo_id;
	GLenum m_elements_type;

    void updateIndexBuffer(const GLsizeiptr& size, const void* data, const GLenum& draw_type) const;

};

#endif /* BAUASIAN_INDEXED_DRAWABLE_HPP */
