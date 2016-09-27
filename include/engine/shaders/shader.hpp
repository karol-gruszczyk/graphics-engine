#ifndef GRAPHICS_ENGINE_SHADER_HPP
#define GRAPHICS_ENGINE_SHADER_HPP

#include <GL/glew.h>
#include <boost/filesystem/path.hpp>
#include "preprocessor.hpp"
#include "../exceptions/shader_compile_exception.hpp"
#include "../exceptions/file_not_found_exception.hpp"


namespace engine
{
	class Shader;
}

class engine::Shader
{
	friend class ShaderProgram;

public:
	Shader(const boost::filesystem::path &path, const GLenum &type);
	virtual ~Shader();
protected:
	GLuint m_shader_id;

	std::string openShaderFile(const boost::filesystem::path &path) const;
};

#endif /* GRAPHICS_ENGINE_SHADER_HPP */
