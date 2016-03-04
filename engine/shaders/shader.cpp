#include "shader.h"
#include <fstream>
#include <streambuf>

using engine::Shader;


engine::Shader::~Shader()
{
	glDeleteShader(m_shader_id);
}

void Shader::loadFromFile(std::string path)
{
	std::ifstream file(path, std::ios::in);
	if (!file.good())
		throw FileNotFoundException(path);


	std::string shader_code((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	file.close();

	initializeShader();
	const GLchar* shader_code_ = shader_code.c_str();
	glShaderSource(m_shader_id, 1, &shader_code_, NULL);
	glCompileShader(m_shader_id);

	GLint success;
	glGetShaderiv(m_shader_id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar info_log[512];
		glGetShaderInfoLog(m_shader_id, 512, nullptr, info_log);
		throw ShaderCompileException(path, info_log);
	}
}
