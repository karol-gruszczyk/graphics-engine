#include "vertex_shader.hpp"


using bauasian::VertexShader;


VertexShader::VertexShader(const boost::filesystem::path& path)
		: Shader(path, GL_VERTEX_SHADER)
{}