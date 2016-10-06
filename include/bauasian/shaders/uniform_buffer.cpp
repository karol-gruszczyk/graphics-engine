#include "uniform_buffer.hpp"


using bauasian::UniformBuffer;

UniformBuffer::UniformBuffer(const GLsizeiptr& data_size, const bauasian::UniformBuffer::BindingPoint& binding_point)
		: m_uniform_block_size(data_size), m_binding_point(binding_point)
{
	glGenBuffers(1, &m_ubo_id);
	glBindBuffer(GL_UNIFORM_BUFFER, m_ubo_id);
	glBufferData(GL_UNIFORM_BUFFER, m_uniform_block_size, nullptr, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, m_binding_point, m_ubo_id);
}

UniformBuffer::~UniformBuffer()
{
	glDeleteBuffers(1, &m_ubo_id);
}

void UniformBuffer::setData(const void* data) const
{
	glBindBuffer(GL_UNIFORM_BUFFER, m_ubo_id);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, m_uniform_block_size, data);
}

void UniformBuffer::setSubData(const GLintptr& offset, const GLsizeiptr& size, const void* data) const
{
	glBindBuffer(GL_UNIFORM_BUFFER, m_ubo_id);
	glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
}

void UniformBuffer::attachUniformBlock(bauasian::ShaderProgram* shader, const std::string& block_name) const
{
	const GLuint block_index = glGetUniformBlockIndex(shader->getId(), block_name.c_str());
	assert(block_index != GL_INVALID_INDEX);
	GLint block_size;
	glGetActiveUniformBlockiv(shader->getId(), block_index, GL_UNIFORM_BLOCK_DATA_SIZE, &block_size);
	assert(m_uniform_block_size == block_size);
	glUniformBlockBinding(shader->getId(), block_index, m_binding_point);
}
