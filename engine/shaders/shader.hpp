#ifndef SHADER_HPP_
#define SHADER_HPP_

#include <GL/glew.h>
#include <boost/filesystem/path.hpp>
#include "preprocessor.hpp"
#include "../exceptions/shader_compile_exception.hpp"
#include "../exceptions/file_not_found_exception.hpp"


namespace engine
{
	class Shader;
}

class engine::Shader abstract
{
	friend class ShaderProgram;
public:
	Shader(boost::filesystem::path path, GLenum type);
	virtual ~Shader();
protected:
	GLuint m_shader_id;

	std::string openShaderFile(boost::filesystem::path path);
};

#endif /* SHADER_HPP_ */
