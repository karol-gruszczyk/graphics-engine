#include "shader_program.hpp"
#include "bauasian/bauasian.hpp"
#include <glm/gtc/type_ptr.hpp>


using bauasian::ShaderProgram;
using bauasian::Shader;


ShaderProgram::ShaderProgram(const std::initializer_list<Shader*>& shaders)
{
	m_shader_program_id = glCreateProgram();
	m_shader_program_created = true;
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
			info_log.resize((unsigned)info_log_length);
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
	if (m_shader_program_created)
		glDeleteProgram(m_shader_program_id);
}

void ShaderProgram::bind() const
{
	glUseProgram(m_shader_program_id);
}

void ShaderProgram::unbind() const
{
	glUseProgram(0);
}

void ShaderProgram::setUniformBool(const std::string& uniform_name, const bool& value) const
{
	bind();
	auto location = glGetUniformLocation(m_shader_program_id, uniform_name.c_str());
	glUniform1i(location, value);
}

void ShaderProgram::setUniformInt(const std::string& uniform_name, const int& value) const
{
	bind();
	auto location = glGetUniformLocation(m_shader_program_id, uniform_name.c_str());
	glUniform1i(location, value);
}

void ShaderProgram::setUniformUInt(const std::string& uniform_name, const unsigned& value) const
{
	bind();
	auto location = glGetUniformLocation(m_shader_program_id, uniform_name.c_str());
	glUniform1ui(location, value);
}

void ShaderProgram::setUniformFloat(const std::string& uniform_name, const float& value) const
{
	bind();
	auto location = glGetUniformLocation(m_shader_program_id, uniform_name.c_str());
	assert(location != -1);
	glUniform1f(location, value);
}
void ShaderProgram::setUniformFloatVector(const std::string& uniform_name, const float* const value,
                                          const GLsizei& count)
{
	bind();
	auto location = glGetUniformLocation(m_shader_program_id, uniform_name.c_str());
	assert(location != -1);
	glUniform1fv(location, count, value);
}

void ShaderProgram::setUniformVector2(const std::string& uniform_name, const glm::vec2& vector) const
{
	bind();
	auto location = glGetUniformLocation(m_shader_program_id, uniform_name.c_str());
	assert(location != -1);
	glUniform2fv(location, 1, glm::value_ptr(vector));
}

void ShaderProgram::setUniformVector3(const std::string& uniform_name, const glm::vec3& vector) const
{
	bind();
	auto location = glGetUniformLocation(m_shader_program_id, uniform_name.c_str());
	assert(location != -1);
	glUniform3fv(location, 1, glm::value_ptr(vector));
}

void ShaderProgram::setUniformMatrix3(const std::string& uniform_name, const glm::mat3& matrix) const
{
	bind();
	auto location = glGetUniformLocation(m_shader_program_id, uniform_name.c_str());
	assert(location != -1);
	glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderProgram::setUniformMatrix4(const std::string& uniform_name, const glm::mat4& matrix) const
{
	bind();
	auto location = glGetUniformLocation(m_shader_program_id, uniform_name.c_str());
	assert(location != -1);
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}
