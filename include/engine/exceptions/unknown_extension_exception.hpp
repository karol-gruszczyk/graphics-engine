#ifndef GRAPHICS_ENGINE_UNKNOWN_EXTENSION_EXCEPTION_HPP
#define GRAPHICS_ENGINE_UNKNOWN_EXTENSION_EXCEPTION_HPP

#include <exception>


namespace engine
{
	class UnknownExtensionException;
}

class engine::UnknownExtensionException : public std::runtime_error
{
public:
	UnknownExtensionException(std::string filename)
			: runtime_error("File '" + filename + "' has an unknown extension")
	{}
};

#endif /* GRAPHICS_ENGINE_UNKNOWN_EXTENSION_EXCEPTION_HPP */
