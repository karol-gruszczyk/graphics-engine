#ifndef ENTITY_H_
#define ENTITY_H_

#include <list>
#include "../../shaders/shader_program.h"

#define VERTEX_ATTRIB_POINTER 0
#define TEXTURE_COORD_ATTRIB_POINTER 1
#define NORMAL_ATTRIB_POINTER 2


namespace engine
{
	class Entity;
}

class engine::Entity abstract
{
	friend class Scene;
public:
	Entity();
	~Entity();

	virtual void render() = 0;
protected:
	GLuint m_vao_id;
	GLuint m_vertex_vbo_id, m_texture_coords_vbo_id;
	bool m_vao_created, m_vertex_vbo_created, m_texture_coords_vbo_created;
	unsigned m_num_vertices;

	glm::mat4 m_pivot_matrix;
	glm::mat4 m_translation_matrix;
	glm::mat4 m_rotation_matrix;
	glm::mat4 m_scale_matrix;

	std::list<ShaderProgram*> m_shaders;

	virtual void updatePivotMatrix() = 0;
	virtual void updateTranslationMatrix() = 0;
	virtual void updateRotationMatrix() = 0;
	virtual void updateScaleMatrix() = 0;
	void updateModelMatrix();
};

#endif /* ENTITY_H_ */
