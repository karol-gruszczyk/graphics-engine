#ifndef BAUASIAN_SHADER_LINK_EXCEPPTION_HPP
#define BAUASIAN_SHADER_LINK_EXCEPPTION_HPP

#include <exception>


namespace bauasian
{
	class ShaderLinkException;
}

class bauasian::ShaderLinkException : public std::runtime_error
{
public:
	ShaderLinkException(std::string error_message)
			: runtime_error("The shader program failed to link shaders"), m_error_message(error_message)
	{}

	std::string& getErrorMessage()
	{
		return m_error_message;
	}

private:
	std::string m_error_message;
};

#endif /* BAUASIAN_SHADER_LINK_EXCEPPTION_HPP */
