#ifndef ENTITY_H_
#define ENTITY_H_

#include <gl/glew.h>
#include <gl/GL.h>

namespace engine
{

	class Entity
	{
	public:
		Entity();
		~Entity();
		
		virtual void render() = 0;
		void bind();
		void unbind();
	protected:
		GLuint m_vao;
		GLuint m_vertex_vbo;
		unsigned m_num_vertices;
	};
}

#endif /* ENTITY_H_ */
