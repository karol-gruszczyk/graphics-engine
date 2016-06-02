#ifndef UNKNOWN_FILE_TYPE_EXCEPTION_H_
#define UNKNOWN_FILE_TYPE_EXCEPTION_H_

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

#endif /* UNKNOWN_FILE_TYPE_EXCEPTION_H_ */
