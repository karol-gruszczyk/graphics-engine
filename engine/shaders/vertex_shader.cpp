#include "vertex_shader.h"

using engine::VertexShader;


VertexShader::VertexShader()
	: Shader()
{}

VertexShader::VertexShader(boost::filesystem::path path)
	: Shader(path)
{
	loadFromFile(path);
}

void VertexShader::loadFromFile(boost::filesystem::path path)
{
	m_shader_id = glCreateShader(GL_VERTEX_SHADER);
	m_shader_created = true;
	Shader::loadFromFile(path);
}
