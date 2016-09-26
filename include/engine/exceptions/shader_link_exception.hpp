#ifndef SHADER_LINK_EXCEPPTION_HPP_
#define SHADER_LINK_EXCEPPTION_HPP_

#include <exception>


namespace engine
{
	class ShaderLinkException;
}

class engine::ShaderLinkException : public std::runtime_error
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

#endif /* SHADER_LINK_EXCEPPTION_HPP_ */
