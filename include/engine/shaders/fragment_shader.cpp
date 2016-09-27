#include "fragment_shader.hpp"


using engine::FragmentShader;


FragmentShader::FragmentShader(const boost::filesystem::path &path)
		: Shader(path, GL_FRAGMENT_SHADER)
{}
