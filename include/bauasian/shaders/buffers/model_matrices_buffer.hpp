#ifndef BAUASIAN_MATRICES_BUFFER_HPP
#define BAUASIAN_MATRICES_BUFFER_HPP

#include "uniform_buffer.hpp"


namespace bauasian
{
	class ModelMatricesBuffer;
}

class bauasian::ModelMatricesBuffer : public UniformBuffer
{
public:
	struct alignas(16) GlslModelMatrices
	{
		glm::mat4 projection_matrix;
		glm::mat4 view_matrix;
		glm::mat4 model_matrix;
		glm::mat4 normal_matrix;
	};

	static ModelMatricesBuffer& getInstance();

	void setProjectionMatrix(const glm::mat4& matrix) const;
	void setViewMatrix(const glm::mat4& matrix) const;
	void setModelMatrix(const glm::mat4& matrix) const;
	void setNormalMatrix(const glm::mat4& matrix) const;

private:
	ModelMatricesBuffer();

};


#endif /* BAUASIAN_MATRICES_BUFFER_HPP */
