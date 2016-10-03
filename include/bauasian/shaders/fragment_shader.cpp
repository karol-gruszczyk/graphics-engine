#include "fragment_shader.hpp"


using bauasian::FragmentShader;


FragmentShader::FragmentShader(const boost::filesystem::path& path)
		: Shader(path, GL_FRAGMENT_SHADER)
{}
