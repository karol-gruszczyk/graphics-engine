#include "shader.h"
#include "../config.h"
#include <fstream>
#include <streambuf>

using engine::Shader;


Shader::~Shader()
{
	if (m_shader_created)
		glDeleteShader(m_shader_id);
}

Shader::Shader()
{}

Shader::Shader(boost::filesystem::path path)
{
	loadFromFile(path);
}

void Shader::loadFromFile(boost::filesystem::path path)
{
	std::ifstream file;
	file.exceptions(std::ifstream::badbit);
	file.open(path.c_str(), std::ios::in);
	if (!file.good())
		throw FileNotFoundException(path);

	std::string shader_code((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	file.close();

	const GLchar* const gl_shader_code = shader_code.c_str();
	glShaderSource(m_shader_id, 1, &gl_shader_code, NULL);
	glCompileShader(m_shader_id);

	GLint info_log_length;
	glGetShaderiv(m_shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
	if (info_log_length > 0)
	{
		std::string info_log;
		info_log.resize(info_log_length);
		glGetShaderInfoLog(m_shader_id, info_log_length, nullptr, &info_log[0]);
		Config::log(info_log);
		GLint success;
		glGetShaderiv(m_shader_id, GL_COMPILE_STATUS, &success);
		if (!success)
			throw ShaderCompileException(path, info_log);
	}
}
