#ifndef BAUASIAN_GLSL_SYNTAX_ERROR_EXCEPTION_HPP
#define BAUASIAN_GLSL_SYNTAX_ERROR_EXCEPTION_HPP

#include <exception>
#include <boost/filesystem/operations.hpp>


namespace bauasian
{
	class GLSLSyntaxErrorException;
}

class bauasian::GLSLSyntaxErrorException : public std::runtime_error
{
public:
	GLSLSyntaxErrorException(boost::filesystem::path shader_path, std::string line_content)
			: std::runtime_error(
			boost::filesystem::canonical(shader_path).string() + ": syntax error near '" + line_content + "'")
	{}
};

#endif /* BAUASIAN_GLSL_SYNTAX_ERROR_EXCEPTION_HPP */
