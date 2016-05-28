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

	virtual void render() = 0;
	virtual glm::mat4& getModelMatrix();
protected:
	GLuint m_vao_id;
	std::list<GLuint> m_vbos;

	glm::mat4 m_pivot_matrix;
	glm::mat4 m_translation_matrix;
	glm::mat4 m_rotation_matrix;
	glm::mat4 m_scale_matrix;

	void createBufferObject(GLenum target, GLsizeiptr data_length, const void* data, GLenum usage = GL_STATIC_DRAW);
	virtual void updatePivotMatrix() = 0;
	virtual void updateTranslationMatrix() = 0;
	virtual void updateRotationMatrix() = 0;
	virtual void updateScaleMatrix() = 0;
};

#endif /* ENTITY_H_ */
