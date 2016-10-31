#include "model_matrices_buffer.hpp"

#include <glm/gtc/type_ptr.hpp>


using bauasian::ModelMatricesBuffer;

ModelMatricesBuffer& ModelMatricesBuffer::getInstance()
{
	static ModelMatricesBuffer instance;
	return instance;
}

void ModelMatricesBuffer::setProjectionMatrix(const glm::mat4& matrix) const
{
	setSubData(0, sizeof(glm::mat4), glm::value_ptr(matrix));
}

void ModelMatricesBuffer::setViewMatrix(const glm::mat4& matrix) const
{
	setSubData(sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(matrix));
}

void ModelMatricesBuffer::setModelMatrix(const glm::mat4& matrix) const
{
	setSubData(2 * sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(matrix));
}

void ModelMatricesBuffer::setNormalMatrix(const glm::mat4& matrix) const
{
	setSubData(3 * sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(matrix));
}

ModelMatricesBuffer::ModelMatricesBuffer()
		: UniformBuffer(sizeof(GlslModelMatrices), UniformBuffer::MODEL_MATRICES)
{}
