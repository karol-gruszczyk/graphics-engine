#ifndef ENTITY_H_
#define ENTITY_H_

#define GLEW_STATIC
#include <GL/glew.h>

#define VERTEX_ATTRIB_POINTER 0
#define NORMAL_ATTRIB_POINTER 1
#define TEXTURE_COORD_ATTRIB_POINTER 2


namespace engine
{
	class Entity;
}

class engine::Entity abstract
{
public:
	Entity();
	~Entity();

	virtual void render() = 0;
protected:
	GLuint m_vao_id;
	GLuint m_vertex_vbo_id;
	unsigned m_num_vertices;

	bool m_vao_initialized, m_vertex_vbo_initialized;
};

#endif /* ENTITY_H_ */
