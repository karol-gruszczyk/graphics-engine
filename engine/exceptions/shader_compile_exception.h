#ifndef SHADER_COMPILE_EXCEPPTION_H_
#define SHADER_COMPILE_EXCEPPTION_H_


#include <exception>


namespace engine
{
	class ShaderCompileException;
}

class engine::ShaderCompileException : public std::runtime_error
{
public:
	ShaderCompileException(std::string path, std::string error_message)
		: runtime_error("The file '" + path + "' could not be compiled"), m_error_message(error_message)
	{}
	std::string& getErrorMessage()
	{
		return m_error_message;
	}
private:
	std::string m_error_message;
};

#endif /* SHADER_COMPILE_EXCEPPTION_H_ */
