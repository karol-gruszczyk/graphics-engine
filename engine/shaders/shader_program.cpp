#include "shader_program.h"
#include "../config.h"
#include <glm/gtc/type_ptr.hpp>

using engine::ShaderProgram;
using engine::Shader;


ShaderProgram::ShaderProgram(std::initializer_list<Shader*> shaders)
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
			info_log.resize(info_log_length);
			glGetProgramInfoLog(m_shader_program_id, info_log_length, nullptr, &info_log[0]);
		}

		if (success == GL_FALSE)
		{
			Config::getInstance().log(info_log, Config::ERROR);
			throw ShaderLinkException(info_log);
		}
		Config::getInstance().log(info_log, Config::WARNING);
	}
	for (auto& shader : shaders)
		glDetachShader(m_shader_program_id, shader->m_shader_id);
}

ShaderProgram::~ShaderProgram()
{
	if (m_shader_program_created)
		glDeleteProgram(m_shader_program_id);
}

void ShaderProgram::bind()
{
	glUseProgram(m_shader_program_id);
}

void ShaderProgram::unbind()
{
	glUseProgram(NULL);
}

void ShaderProgram::setUniformUint(std::string uniform_name, unsigned value)
{
	bind();
	auto location = glGetUniformLocation(m_shader_program_id, uniform_name.c_str());
	glUniform1ui(location, value);
}

void ShaderProgram::setUniformFloat(std::string uniform_name, float value)
{
	bind();
	auto location = glGetUniformLocation(m_shader_program_id, uniform_name.c_str());
	assert(location != -1);
	glUniform1f(location, value);
}

void ShaderProgram::setUniformVector3(std::string uniform_name, glm::vec3 vector)
{
	bind();
	auto location = glGetUniformLocation(m_shader_program_id, uniform_name.c_str());
	assert(location != -1);
	glUniform3fv(location, 1, glm::value_ptr(vector));
}

void ShaderProgram::setUniformMatrix4(std::string uniform_name, glm::mat4 matrix)
{
	bind();
	auto location = glGetUniformLocation(m_shader_program_id, uniform_name.c_str());
	assert(location != -1);
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}
