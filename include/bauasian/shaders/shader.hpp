#ifndef BAUASIAN_SHADER_HPP
#define BAUASIAN_SHADER_HPP

#include <map>
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
	enum ShaderType
	{
		VERTEX_SHADER = GL_VERTEX_SHADER, FRAGMENT_SHADER = GL_FRAGMENT_SHADER
	};

	Shader(const boost::filesystem::path& path, const ShaderType& type,
	       const std::map<std::string, std::string>& defines = {});
	Shader(const Shader&) = delete;
	Shader& operator=(const Shader&) = delete;
	virtual ~Shader();

protected:
	GLuint m_shader_id;

};

#endif /* BAUASIAN_SHADER_HPP */
