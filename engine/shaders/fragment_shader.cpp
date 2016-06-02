#include "fragment_shader.h"

using engine::FragmentShader;


FragmentShader::FragmentShader(boost::filesystem::path path)
	: Shader(path, GL_FRAGMENT_SHADER)
{}
