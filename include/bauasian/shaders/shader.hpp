#ifndef GRAPHICS_ENGINE_SHADER_HPP
#define GRAPHICS_ENGINE_SHADER_HPP

#include <GL/glew.h>
#include <boost/filesystem/path.hpp>
#include "preprocessor.hpp"
#include "bauasian/exceptions/shader_compile_exception.hpp"
#include "bauasian/exceptions/file_not_found_exception.hpp"


namespace bauasian
{
	class Shader;
}

class bauasian::Shader
{
	friend class ShaderProgram;

public:
	Shader(const boost::filesystem::path& path, const GLenum& type);
	virtual ~Shader();
protected:
	GLuint m_shader_id;

	std::string openShaderFile(const boost::filesystem::path& path) const;
};

#endif /* GRAPHICS_ENGINE_SHADER_HPP */
