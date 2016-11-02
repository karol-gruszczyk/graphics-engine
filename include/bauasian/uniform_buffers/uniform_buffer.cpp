#include "uniform_buffer.hpp"


using bauasian::UniformBuffer;
using bauasian::ShaderProgram;

UniformBuffer::UniformBuffer(const GLsizeiptr& data_size, const GLuint& binding_point)
		: m_uniform_block_size(data_size), m_binding_point(binding_point)
{
	glCreateBuffers(1, &m_ubo_id);
	glNamedBufferData(m_ubo_id, m_uniform_block_size, nullptr, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, m_binding_point, m_ubo_id);
	bind();
}

UniformBuffer::~UniformBuffer()
{
	glDeleteBuffers(1, &m_ubo_id);
}

void UniformBuffer::setData(const void* data) const
{
	glNamedBufferSubData(m_ubo_id, 0, m_uniform_block_size, data);
}

void UniformBuffer::setSubData(const GLintptr& offset, const GLsizeiptr& size, const void* data) const
{
	glNamedBufferSubData(m_ubo_id, offset, size, data);
}

void UniformBuffer::attachUniformBlock(ShaderProgram* shader, const std::string& block_name) const
{
	const GLuint block_index = glGetUniformBlockIndex(shader->getId(), block_name.c_str());
	assert(block_index != GL_INVALID_INDEX);
	GLint block_size;
	glGetActiveUniformBlockiv(shader->getId(), block_index, GL_UNIFORM_BLOCK_DATA_SIZE, &block_size);
	assert(m_uniform_block_size == block_size);
	glUniformBlockBinding(shader->getId(), block_index, m_binding_point);
}

void UniformBuffer::bind() const
{
	glBindBufferBase(GL_UNIFORM_BUFFER, m_binding_point, m_ubo_id);
}

void UniformBuffer::bind(const GLuint& binding_point) const
{
	glBindBufferBase(GL_UNIFORM_BUFFER, binding_point, m_ubo_id);
}
