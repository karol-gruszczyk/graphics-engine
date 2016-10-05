#ifndef BAUASIAN_OPEN_GL_VERSION_TOO_LOW_EXCEPTION_HPP
#define BAUASIAN_OPEN_GL_VERSION_TOO_LOW_EXCEPTION_HPP

#define BAUASIAN_REQUIRED_OPEN_GL_MAJOR 4
#define BAUASIAN_REQUIRED_OPEN_GL_MINOR 1
/* requirements:
 * 4.1 - glProgramUniform
 */

#include <exception>


namespace bauasian
{
	class OpenGLVersionTooLow;
}

class bauasian::OpenGLVersionTooLow : public std::runtime_error
{
public:
	OpenGLVersionTooLow(const int& current_major, const int& current_minor)
			: std::runtime_error("You are using OpenGL "
			                     + std::to_string(current_major) + "." + std::to_string(current_minor) +
			                     ". Required version is " + std::to_string(BAUASIAN_REQUIRED_OPEN_GL_MAJOR) + "."
			                     + std::to_string(BAUASIAN_REQUIRED_OPEN_GL_MINOR))
	{}
};

#endif /* BAUASIAN_OPEN_GL_VERSION_TOO_LOW_EXCEPTION_HPP */
