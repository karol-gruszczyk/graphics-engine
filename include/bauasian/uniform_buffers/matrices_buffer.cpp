#include "matrices_buffer.hpp"

#include <glm/gtc/type_ptr.hpp>


using bauasian::MatricesBuffer;

MatricesBuffer& MatricesBuffer::getInstance()
{
	static MatricesBuffer instance;
	return instance;
}

void MatricesBuffer::setModelMatrix(const glm::mat4& matrix) const
{
	setSubData(0, sizeof(glm::mat4), glm::value_ptr(matrix));
}

void MatricesBuffer::setNormalMatrix(const glm::mat4& matrix) const
{
	setSubData(sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(matrix));
}

MatricesBuffer::MatricesBuffer()
		: UniformBuffer(sizeof(GlslMatricesBuffer), UniformBuffer::MATRICES)
{}
