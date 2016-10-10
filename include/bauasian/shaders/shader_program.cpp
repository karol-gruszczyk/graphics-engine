#include "shader_program.hpp"
#include "bauasian/bauasian.hpp"
#include <glm/gtc/type_ptr.hpp>


using bauasian::ShaderProgram;
using bauasian::Shader;


ShaderProgram::ShaderProgram(const std::initializer_list<Shader*>& shaders)
{
	m_shader_program_id = glCreateProgram();
	for (auto& shader : shaders)
		glAttachShader(m_shader_program_id, shader->m_shader_id);
	glLinkProgram(m_shader_program_id);

	GLint success, info_log_length;
	glGetProgramiv(m_shader_program_id, GL_LINK_STATUS, &success);
	glGetProgramiv(m_shader_program_id, GL_INFO_LOG_LENGTH, &info_log_length);
	if (success == GL_FALSE || info_log_length > 0)
	{
		std::string info_log;
		if (info_log_length > 0)
		{
			info_log.resize((unsigned) info_log_length);
			glGetProgramInfoLog(m_shader_program_id, info_log_length, nullptr, &info_log[0]);
		}

		if (success == GL_FALSE)
		{
			Bauasian::getInstance().logError(info_log);
			throw ShaderLinkException(info_log);
		}
		Bauasian::getInstance().logWarning(info_log);
	}
	for (auto& shader : shaders)
		glDetachShader(m_shader_program_id, shader->m_shader_id);
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(m_shader_program_id);
}

const GLuint& ShaderProgram::getId() const
{
	return m_shader_program_id;
}

void ShaderProgram::use() const
{
	glUseProgram(m_shader_program_id);
}

const GLint ShaderProgram::getUniformLocation(const std::string& uniform_name) const
{
	const GLint location = glGetUniformLocation(m_shader_program_id, uniform_name.c_str());
	assert(location != -1);
	return location;
}

void ShaderProgram::setUniform(const GLint& location, const bool& value) const
{
	glProgramUniform1i(m_shader_program_id, location, value);
}

void ShaderProgram::setUniform(const GLint& location, const float& value) const
{
	glProgramUniform1f(m_shader_program_id, location, value);
}

void ShaderProgram::setUniform(const GLint& location, const double& value) const
{
	glProgramUniform1d(m_shader_program_id, location, value);
}

void ShaderProgram::setUniform(const GLint& location, const int& value) const
{
	glProgramUniform1i(m_shader_program_id, location, value);
}

void ShaderProgram::setUniform(const GLint& location, const unsigned& value) const
{
	glProgramUniform1ui(m_shader_program_id, location, value);
}

void ShaderProgram::setUniform(const GLint& location, const glm::vec2& vector, const GLsizei& count) const
{
	glProgramUniform2fv(m_shader_program_id, location, count, glm::value_ptr(vector));
}

void ShaderProgram::setUniform(const GLint& location, const glm::vec3& vector, const GLsizei& count) const
{
	glProgramUniform3fv(m_shader_program_id, location, count, glm::value_ptr(vector));
}

void ShaderProgram::setUniform(const GLint& location, const glm::vec4& vector, const GLsizei& count) const
{
	glProgramUniform4fv(m_shader_program_id, location, count, glm::value_ptr(vector));
}

void ShaderProgram::setUniform(const GLint& location, const glm::mat3& matrix, const GLsizei& count) const
{
	glProgramUniformMatrix3fv(m_shader_program_id, location, count, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderProgram::setUniform(const GLint& location, const glm::mat4& matrix, const GLsizei& count) const
{
	glProgramUniformMatrix4fv(m_shader_program_id, location, count, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderProgram::setUniform(const GLint& location, const float* const values_ptr, const GLsizei& count) const
{
	glProgramUniform1fv(m_shader_program_id, location, count, values_ptr);
}

void ShaderProgram::setUniform(const GLint& location, const double* const values_ptr, const GLsizei& count) const
{
	glProgramUniform1dv(m_shader_program_id, location, count, values_ptr);
}

void ShaderProgram::setUniform(const GLint& location, const int* const values_ptr, const GLsizei& count) const
{
	glProgramUniform1iv(m_shader_program_id, location, count, values_ptr);
}

void ShaderProgram::setUniform(const GLint& location, const unsigned* const values_ptr, const GLsizei& count) const
{
	glProgramUniform1uiv(m_shader_program_id, location, count, values_ptr);
}
