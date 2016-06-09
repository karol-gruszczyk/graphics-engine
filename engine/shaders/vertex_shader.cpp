#include "vertex_shader.hpp"

using engine::VertexShader;


VertexShader::VertexShader(boost::filesystem::path path)
	: Shader(path, GL_VERTEX_SHADER)
{}
