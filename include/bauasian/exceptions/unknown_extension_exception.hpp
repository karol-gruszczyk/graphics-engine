#ifndef BAUASIAN_UNKNOWN_EXTENSION_EXCEPTION_HPP
#define BAUASIAN_UNKNOWN_EXTENSION_EXCEPTION_HPP

#include <exception>


namespace bauasian
{
	class UnknownExtensionException;
}

class bauasian::UnknownExtensionException : public std::runtime_error
{
public:
	UnknownExtensionException(std::string filename)
			: runtime_error("File '" + filename + "' has an unknown extension")
	{}
};

#endif /* BAUASIAN_UNKNOWN_EXTENSION_EXCEPTION_HPP */
