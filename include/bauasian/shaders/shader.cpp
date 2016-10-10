#include "shader.hpp"
#include "bauasian/bauasian.hpp"


using bauasian::Shader;
using bauasian::Preprocessor;

std::map<Shader::ShaderType, GLenum> Shader::s_shader_type = {
		{ VERTEX_SHADER,   GL_VERTEX_SHADER },
		{ FRAGMENT_SHADER, GL_FRAGMENT_SHADER },
};

Shader::Shader(const boost::filesystem::path& path, const ShaderType& type)
{
	const auto& shader_path = Bauasian::getInstance().getShaderPath() / path;

	std::string shader_code(openShaderFile(shader_path));

	const GLchar* gl_shader_code = shader_code.c_str();
	m_shader_id = glCreateShader(s_shader_type[type]);
	glShaderSource(m_shader_id, 1, &gl_shader_code, nullptr);
	glCompileShader(m_shader_id);

	GLint success, info_log_length;
	glGetShaderiv(m_shader_id, GL_COMPILE_STATUS, &success);
	glGetShaderiv(m_shader_id, GL_INFO_LOG_LENGTH, &info_log_length);

	if (success == GL_FALSE || info_log_length > 0)
	{
		std::string info_log;
		if (info_log_length > 0)
		{
			info_log.resize((unsigned long)info_log_length);
			glGetShaderInfoLog(m_shader_id, info_log_length, nullptr, &info_log[0]);
		}
		info_log = "Shader file '" + boost::filesystem::canonical(shader_path).string() + "' raised the following message:\n" +
		           info_log;
		if (success == GL_FALSE)
		{
			Bauasian::getInstance().logError(info_log);
			throw ShaderCompileException(shader_path, info_log);
		}
		Bauasian::getInstance().logWarning(info_log);
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
