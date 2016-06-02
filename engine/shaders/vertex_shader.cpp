#include "vertex_shader.h"

using engine::VertexShader;


VertexShader::VertexShader(boost::filesystem::path path)
	: Shader(path, GL_VERTEX_SHADER)
{}
