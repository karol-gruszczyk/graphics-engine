#include "shader_mixin.hpp"


using bauasian::ShaderMixin;
using bauasian::ShaderProgram;

ShaderMixin::ShaderMixin(const boost::filesystem::path& vs_path, const boost::filesystem::path& fs_path)
{
	const auto vs = std::make_unique<Shader>(vs_path, Shader::VERTEX_SHADER);
	const auto fs = std::make_unique<Shader>(fs_path, Shader::FRAGMENT_SHADER);
	m_shader = std::make_unique<ShaderProgram>(std::initializer_list<Shader*>{ vs.get(), fs.get() });
}

const ShaderProgram* const ShaderMixin::getShader() const
{
	return m_shader.get();
}
