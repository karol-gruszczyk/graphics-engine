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
		VERTEX_SHADER, FRAGMENT_SHADER
	};

	Shader(const boost::filesystem::path& path, const ShaderType& type);
	virtual ~Shader();
protected:
	GLuint m_shader_id;
	static std::map<ShaderType, GLenum> s_shader_type;

	std::string openShaderFile(const boost::filesystem::path& path) const;
};

#endif /* BAUASIAN_SHADER_HPP */
