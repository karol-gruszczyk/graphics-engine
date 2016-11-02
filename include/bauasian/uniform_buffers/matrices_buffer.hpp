#ifndef BAUASIAN_MATRICES_BUFFER_HPP
#define BAUASIAN_MATRICES_BUFFER_HPP

#include "uniform_buffer.hpp"


namespace bauasian
{
	class MatricesBuffer;
}

class bauasian::MatricesBuffer : public UniformBuffer
{
public:
	struct alignas(16) GlslMatricesBuffer
	{
		glm::mat4 model_matrix;
		glm::mat4 normal_matrix;
	};

	static MatricesBuffer& getInstance();

	void setModelMatrix(const glm::mat4& matrix) const;
	void setNormalMatrix(const glm::mat4& matrix) const;

private:
	MatricesBuffer();

};


#endif /* BAUASIAN_MATRICES_BUFFER_HPP */
