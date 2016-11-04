#ifndef BAUASIAN_SHADER_PROFRAM_HPP
#define BAUASIAN_SHADER_PROFRAM_HPP

#include <initializer_list>
#include <glm/glm.hpp>
#include "shader.hpp"
#include "bauasian/exceptions/shader_link_exception.hpp"


namespace bauasian
{
	class ShaderProgram;
}

class bauasian::ShaderProgram final
{
public:
	ShaderProgram(const std::initializer_list<const Shader*>& shaders);
	~ShaderProgram();

	GLuint getId() const;
	void use() const;
	GLint getUniformLocation(const std::string& uniform_name) const;
	void setUniform(GLint location, bool value) const;
	void setUniform(GLint location, float value) const;
	void setUniform(GLint location, double value) const;
	void setUniform(GLint location, int value) const;
	void setUniform(GLint location, unsigned value) const;
	void setUniform(GLint location, const glm::vec2& vector, GLsizei count = 1) const;
	void setUniform(GLint location, const glm::vec3& vector, GLsizei count = 1) const;
	void setUniform(GLint location, const glm::vec4& vector, GLsizei count = 1) const;
	void setUniform(GLint location, const glm::mat3& matrix, GLsizei count = 1) const;
	void setUniform(GLint location, const glm::mat4& matrix, GLsizei count = 1) const;
	void setUniform(GLint location, const float* values_ptr, GLsizei count) const;
	void setUniform(GLint location, const double* values_ptr, GLsizei count) const;
	void setUniform(GLint location, const int* values_ptr, GLsizei count) const;
	void setUniform(GLint location, const unsigned* values_ptr, GLsizei count) const;
	
private:
	GLuint m_shader_program_id;
};

#endif /* BAUASIAN_SHADER_PROFRAM_HPP */
