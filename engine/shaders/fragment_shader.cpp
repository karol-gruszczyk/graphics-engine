#include "fragment_shader.h"

using engine::FragmentShader;


FragmentShader::FragmentShader()
	: Shader()
{}

FragmentShader::FragmentShader(boost::filesystem::path path)
	: Shader(path)
{
	loadFromFile(path);
}

void FragmentShader::loadFromFile(boost::filesystem::path path)
{
	m_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
	m_shader_created = true;
	Shader::loadFromFile(path);
}
