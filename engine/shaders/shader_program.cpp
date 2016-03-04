#include "shader_program.h"

using engine::ShaderProgram;


ShaderProgram::~ShaderProgram()
{
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

void ShaderProgram::create(std::vector<engine::Shader*> shaders)
{
	m_shader_program_id = glCreateProgram();
	for (auto& shader : shaders)
		glAttachShader(m_shader_program_id, shader->m_shader_id);
	glLinkProgram(m_shader_program_id);

	GLint success;
	glGetProgramiv(m_shader_program_id, GL_LINK_STATUS, &success);
	if (!success)
	{
		GLchar info_log[512];
		glGetProgramInfoLog(m_shader_program_id, 512, nullptr, info_log);
		throw ShaderLinkException(info_log);
	}
}
