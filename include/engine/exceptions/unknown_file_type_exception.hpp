#ifndef GRAPHICS_ENGINE_UNKNOWN_FILE_TYPE_EXCEPTION_HPP
#define GRAPHICS_ENGINE_UNKNOWN_FILE_TYPE_EXCEPTION_HPP

#include <exception>
#include <boost/filesystem/operations.hpp>


namespace engine
{
	class UnknownFileTypeException;
}

class engine::UnknownFileTypeException : public std::runtime_error
{
public:
	UnknownFileTypeException(boost::filesystem::path path)
			: runtime_error("The file '" + boost::filesystem::canonical(path).string() + "' is of an unknown file type")
	{}
};

#endif /* GRAPHICS_ENGINE_UNKNOWN_FILE_TYPE_EXCEPTION_HPP */
