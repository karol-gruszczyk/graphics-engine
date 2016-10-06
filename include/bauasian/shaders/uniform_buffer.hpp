#ifndef BAUASIAN_UNIFORM_BUFFER_HPP
#define BAUASIAN_UNIFORM_BUFFER_HPP


#include "shader_program.hpp"
#include <GL/glew.h>


namespace bauasian
{
	class UniformBuffer;
}

class bauasian::UniformBuffer
{
public:
	enum BindingPoint
	{
		MATERIAL
	};
	UniformBuffer(const GLsizeiptr& data_size, const void* data, const BindingPoint& binding_point);
	~UniformBuffer();

	void updateData(const void* data) const;
	void updateSubData(const GLintptr& offset, const GLsizeiptr& size, const void* data) const;
	void attachUniformBlock(ShaderProgram* shader, const std::string& block_name) const;

private:
	GLuint m_ubo_id, m_binding_point;
	GLsizeiptr m_uniform_block_size;
};

#endif /* BAUASIAN_UNIFORM_BUFFER_HPP */
