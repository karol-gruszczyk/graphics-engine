#include "shader.hpp"
#include "engine/engine.hpp"


using engine::Shader;
using engine::Preprocessor;


Shader::Shader(const boost::filesystem::path& path, const GLenum& type)
{
	std::string shader_code(openShaderFile(path));

	const GLchar* const gl_shader_code = shader_code.c_str();
	m_shader_id = glCreateShader(type);
	glShaderSource(m_shader_id, 1, &gl_shader_code, NULL);
	glCompileShader(m_shader_id);

	GLint success, info_log_length;
	glGetShaderiv(m_shader_id, GL_COMPILE_STATUS, &success);
	glGetShaderiv(m_shader_id, GL_INFO_LOG_LENGTH, &info_log_length);

	if (success == GL_FALSE || info_log_length > 0)
	{
		std::string info_log;
		if (info_log_length > 0)
		{
			info_log.resize(info_log_length);
			glGetShaderInfoLog(m_shader_id, info_log_length, nullptr, &info_log[0]);
		}
		info_log = "Shader file '" + boost::filesystem::canonical(path).string() + "' raised the following message:\n" +
		           info_log;
		if (success == GL_FALSE)
		{
			Engine::getInstance().logError(info_log);
			throw ShaderCompileException(path, info_log);
		}
		Engine::getInstance().logWarning(info_log);
	}
}

Shader::~Shader()
{
	glDeleteShader(m_shader_id);
}

std::string Shader::openShaderFile(const boost::filesystem::path& path) const
{
	Preprocessor preprocessor(path);
	return preprocessor.getSourceCode();
}
