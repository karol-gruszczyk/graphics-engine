#ifndef BAUASIAN_UNIFORM_BUFFER_HPP
#define BAUASIAN_UNIFORM_BUFFER_HPP

#include "bauasian/shaders/shader_program.hpp"

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
		MATERIAL, MATRICES, CAMERA, BASIC_MATERIAL, DIRECTIONAL_LIGHT, POINT_LIGHT, SPOT_LIGHT
	};
	UniformBuffer(GLsizeiptr data_size, GLuint binding_point);
	~UniformBuffer();

	void setData(const void* data) const;
	void setSubData(GLintptr offset, GLsizeiptr size, const void* data) const;
	void attachUniformBlock(const ShaderProgram* shader, const std::string& block_name) const;
	void bind() const;

private:
	GLuint m_ubo_id;
	GLsizeiptr m_uniform_block_size;
	GLuint m_binding_point;

};

#endif /* BAUASIAN_UNIFORM_BUFFER_HPP */
