#ifndef ENTITY_H_
#define ENTITY_H_

#include <list>
#include "../../shaders/shader_program.h"

#define POSITION_ATTRIB_POINTER 0
#define TEXTURE_COORD_ATTRIB_POINTER 1
#define NORMAL_ATTRIB_POINTER 2


namespace engine
{
	class Entity;
}

class engine::Entity abstract
{
public:
	Entity();
	virtual ~Entity();

	virtual void render();
	virtual glm::mat4& getModelMatrix();
protected:
	GLuint m_vao_id;
	std::list<GLuint> m_vbos;
	GLenum m_draw_mode;
	GLuint m_elements_size;
	GLenum m_elements_type;

	glm::mat4 m_model_matrix;

	void setupRendering(GLenum draw_mode, GLuint elements_size, GLenum elements_type);
	void createBufferObject(GLenum target, GLsizeiptr data_length, const void* data, GLenum usage = GL_STATIC_DRAW);
};

#endif /* ENTITY_H_ */
