#ifndef BAUASIAN_SHADER_MIXIN_HPP
#define BAUASIAN_SHADER_MIXIN_HPP

#include "bauasian/shaders/shader_program.hpp"

#include <boost/filesystem/path.hpp>


namespace bauasian
{
	class ShaderMixin;
}

class bauasian::ShaderMixin
{
public:
	ShaderMixin(const boost::filesystem::path& vs_path, const boost::filesystem::path& fs_path);

	const ShaderProgram* const getShader() const;

protected:
	std::unique_ptr<ShaderProgram> m_shader;

};

#endif /* BAUASIAN_SHADER_MIXIN_HPP */
