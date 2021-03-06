#ifndef BAUASIAN_SHADER_COMPILE_EXCEPPTION_HPP
#define BAUASIAN_SHADER_COMPILE_EXCEPPTION_HPP

#include <exception>
#include <boost/filesystem/operations.hpp>


namespace bauasian
{
	class ShaderCompileException;
}

class bauasian::ShaderCompileException : public std::runtime_error
{
public:
	ShaderCompileException(boost::filesystem::path path, std::string error_message)
			: runtime_error("The file '" + boost::filesystem::canonical(path).string() + "' could not be compiled"),
			  m_error_message(error_message)
	{}

	std::string& getErrorMessage()
	{
		return m_error_message;
	}

private:
	std::string m_error_message;
};

#endif /* BAUASIAN_SHADER_COMPILE_EXCEPPTION_HPP */
