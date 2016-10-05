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
	ShaderProgram(const std::initializer_list<Shader*>& shaders);
	~ShaderProgram();

	void use() const;

	// TODO: should be removed in next release, as its extremely slow
	void setUniformBool(const std::string& uniform_name, const bool& value) const;
	void setUniformFloat(const std::string& uniform_name, const float& value) const;
	void setUniformFloatVector(const std::string& uniform_name, const float* const value, const GLsizei& count);
	void setUniformInt(const std::string& uniform_name, const int& value) const;
	void setUniformUInt(const std::string& uniform_name, const unsigned& value) const;
	void setUniformVector2(const std::string& uniform_name, const glm::vec2& vector) const;
	void setUniformVector3(const std::string& uniform_name, const glm::vec3& vector) const;
	void setUniformMatrix3(const std::string& uniform_name, const glm::mat3& matrix) const;
	void setUniformMatrix4(const std::string& uniform_name, const glm::mat4& matrix) const;

	const GLint& getUniformLocation(const std::string& uniform_name);
	void setUniform(const GLint& location, const bool& value) const;
	void setUniform(const GLint& location, const float& value) const;
	void setUniform(const GLint& location, const double& value) const;
	void setUniform(const GLint& location, const int& value) const;
	void setUniform(const GLint& location, const unsigned& value) const;
	void setUniform(const GLint& location, const glm::vec2& vector) const;
	void setUniform(const GLint& location, const glm::vec3& vector) const;
	void setUniform(const GLint& location, const glm::vec4& vector) const;
	void setUniform(const GLint& location, const glm::mat3& matrix) const;
	void setUniform(const GLint& location, const glm::mat4& matrix) const;
	void setUniformArray(const GLint& location, const float* const values_ptr, const GLsizei& count) const;
	void setUniformArray(const GLint& location, const double* const values_ptr, const GLsizei& count) const;
	void setUniformArray(const GLint& location, const int* const values_ptr, const GLsizei& count) const;
	void setUniformArray(const GLint& location, const unsigned* const values_ptr, const GLsizei& count) const;
private:
	GLuint m_shader_program_id;
};

#endif /* BAUASIAN_SHADER_PROFRAM_HPP */
