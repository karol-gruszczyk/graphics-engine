#ifndef BAUASIAN_ENTITY_HPP
#define BAUASIAN_ENTITY_HPP

#include <list>
#include "bauasian/shaders/shader_program.hpp"


#define POSITION_ATTRIB_POINTER 0
#define TEXTURE_COORD_ATTRIB_POINTER 1
#define NORMAL_ATTRIB_POINTER 2


namespace bauasian
{
	class Entity;
}

class bauasian::Entity
{
public:
	Entity();
	virtual ~Entity();

	virtual void render() const;
	const glm::mat4& getModelMatrix() const;

protected:
	GLuint m_vao_id;
	std::vector<GLuint> m_vbos;
	GLenum m_draw_mode;
	GLuint m_indices_size;
	GLenum m_elements_type;

	glm::mat4 m_model_matrix;

	void setupRendering(GLenum draw_mode, GLuint elements_size, GLenum elements_type);
	void createBufferObject(GLenum target, GLsizeiptr data_length, const void* data, GLenum usage = GL_STATIC_DRAW);
};

#endif /* BAUASIAN_ENTITY_HPP */
