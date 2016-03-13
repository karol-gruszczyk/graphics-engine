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
	GLuint m_index_vbo_id, m_position_vbo_id, m_texture_coord_vbo_id;
	bool m_index_vbo_created, m_vao_created, m_position_vbo_created, m_texture_coord_vbo_created;

	glm::mat4 m_pivot_matrix;
	glm::mat4 m_translation_matrix;
	glm::mat4 m_rotation_matrix;
	glm::mat4 m_scale_matrix;

	virtual void initBuffers();
	virtual void updatePivotMatrix() = 0;
	virtual void updateTranslationMatrix() = 0;
	virtual void updateRotationMatrix() = 0;
	virtual void updateScaleMatrix() = 0;
};

#endif /* ENTITY_H_ */
